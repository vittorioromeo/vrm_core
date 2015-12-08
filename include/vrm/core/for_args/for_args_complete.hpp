// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <utility>

#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/type_traits.hpp>
#include <vrm/core/static_if.hpp>
#include <vrm/core/args_utils.hpp>
#include <vrm/core/tuple_utils/apply.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

// TODO: temp
#include <iostream>
#include <typeinfo>

// TODO: to test, implement "std:cin choice switch" that returns choice int or
// executes choice function


VRM_CORE_NAMESPACE
{
    struct no_return
    {
    };

    namespace impl
    {
        template <typename TReturn>
        struct control_flow
        {
            template <sz_t TI = 0>
            VRM_CORE_ALWAYS_INLINE constexpr auto get() const noexcept
            {
                return decltype(std::get<TI>(TReturn{})){};
            }
        };

        template <sz_t TI = 0, typename T>
        VRM_CORE_ALWAYS_INLINE constexpr auto unwrap(T) noexcept
        {
            return T{}.template get<TI>();
        }

        struct break_t_base
        {
        };

        struct skip_t_base
        {
        };

        template <typename TReturn>
        struct break_t : control_flow<TReturn>, break_t_base
        {
        };

        template <typename TReturn, sz_t TSkipCount>
        struct skip_t : control_flow<TReturn>, skip_t_base
        {
            using skip_ic = sz_t_<TSkipCount>;
        };

        template <typename TReturn>
        using continue_t = skip_t<TReturn, 0>;

        using void_continue_t = continue_t<std::tuple<no_return>>;

        // Aliases.
        template <typename T>
        using is_break = std::is_base_of<break_t_base, std::decay_t<T>>;

        template <typename T>
        using is_skip = std::is_base_of<skip_t_base, std::decay_t<T>>;



        // Wish we had `constexpr` lambdas.
        struct zero_returner
        {
            template <typename T>
            constexpr auto operator()(T)
            {
                return 0;
            }
        };

        struct skip_value_returner
        {
            template <typename T>
            constexpr auto operator()(T)
            {
                return typename T::skip_ic{};
            }
        };

        template <typename T>
        constexpr auto get_continue_count() noexcept
        {
            // If the return type is skip:
            return static_if(is_skip<T>{})
                // `true` branch -> return its inner value.
                .then(impl::skip_value_returner{})
                // `else` branch -> return `0`.
                .else_(impl::zero_returner{})
                // `wrap` is necessary to handle `void`.
                (T{});
        }

        template <sz_t TIteration, sz_t TArgIndex, typename TLastReturn>
        struct static_for_metadata
        {
            using last_return_type = TLastReturn;
            using this_type =
                static_for_metadata<TIteration, TArgIndex, TLastReturn>;

            VRM_CORE_ALWAYS_INLINE constexpr auto iteration() noexcept
            {
                return TIteration;
            }

            VRM_CORE_ALWAYS_INLINE constexpr auto arg_index() noexcept
            {
                return TArgIndex;
            }


            VRM_CORE_ALWAYS_INLINE constexpr auto has_no_return() noexcept
            {
                return std::is_same<decltype(get()), no_return>{};
            }

            template <sz_t TI = 0>
            VRM_CORE_ALWAYS_INLINE constexpr auto get() const noexcept
            {
                return unwrap<TI>(last_return_type{});
            }


            template <typename TSkip, typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr auto skip_with(
                TSkip, Ts...) noexcept
            {
                return impl::skip_t<std::tuple<Ts...>, TSkip{}>{};
            }

            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr auto continue_with(
                Ts... xs) noexcept
            {
                return skip_with(int_v<0>, xs...);
            }

            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr auto break_with(Ts...) noexcept
            {
                return impl::break_t<std::tuple<Ts...>>{};
            }



            template <typename TReturn = no_return>
            VRM_CORE_ALWAYS_INLINE constexpr auto break_(TReturn = {}) noexcept
            {
                return break_with(TReturn{});
            }

            template <typename TSkip, typename TReturn = no_return>
            VRM_CORE_ALWAYS_INLINE constexpr auto skip(
                TSkip, TReturn = {}) noexcept
            {
                return skip_with(TSkip{}, TReturn{});
            }

            template <typename TReturn = no_return>
            VRM_CORE_ALWAYS_INLINE constexpr auto continue_(
                TReturn = {}) noexcept
            {
                return continue_with(TReturn{});
            }
        };


        template <typename T>
        using adapt_return_type = std::conditional_t< // .
            std::is_same<void, T>{},                  // .
            void_continue_t,                          // .
            T>;



        template <sz_t TArity, typename TFunctionToCall>
        struct static_for_result : TFunctionToCall
        {
            VRM_CORE_STATIC_ASSERT_NM(TArity > 0);

        public:
            static constexpr sz_t arity{TArity};

        private:
            template <sz_t TIteration, sz_t TArgIndex, typename TLastResult>
            using metadata =
                static_for_metadata<TIteration, TArgIndex, TLastResult>;

        private:
            VRM_CORE_ALWAYS_INLINE auto& as_f_to_call() noexcept
            {
                return to_base<TFunctionToCall>(*this);
            }



        public:
            template <typename TFFwd>
            VRM_CORE_ALWAYS_INLINE static_for_result(TFFwd&& f) noexcept
                : TFunctionToCall(FWD(f))
            {
            }

            template <typename TCurrRet, typename TCurrDataType, typename... Ts>
            VRM_CORE_ALWAYS_INLINE decltype(auto) continue_(
                TCurrDataType cm, Ts&&... xs)
            {
                // Alias previous metadata.
                constexpr auto previous_iteration(cm.iteration());
                constexpr auto previous_arg_index(cm.arg_index());

                // Compute number of arguments to skip from previous return
                // type.
                constexpr auto num_skip(get_continue_count<TCurrRet>());

                // Compute next metadata.

                // Next iteration is always incremented by one.
                // Skipped arguments are not counted.
                constexpr auto next_iteration(previous_iteration + 1);

                // `arg_index` is incremented by one plus the count of skipped
                // arguments.
                constexpr auto next_arg_index(
                    previous_arg_index + 1 + num_skip);

                // Executes the next iterator of the loop by applying all
                // arguments, starting from TArity, to the `impl_` function.

                using next_data =
                    metadata<next_iteration, next_arg_index, TCurrRet>;

                constexpr auto skips(num_skip + 1);

                constexpr auto slice_begin(TArity * skips);

                return call_with_all_args_from<slice_begin>(
                    get_impl_wrapper(next_data{}), FWD(xs)...);
            }

            template <typename TDataType>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) get_fn_wrapper(
                TDataType) noexcept
            {
                return [this](auto&&... xs) -> decltype(auto)
                {
                    return this->as_f_to_call()(TDataType{}, FWD(xs)...);
                };
            }

            template <typename TDataType>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) get_impl_wrapper(
                TDataType) noexcept
            {
                return [this](auto&&... xs) -> decltype(auto)
                {
                    return this->impl_(TDataType{}, FWD(xs)...);
                };
            }

            template <typename TDataType, typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) call_with_arity(
                TDataType, Ts&&... xs)
            {
                // Calls the "stored" function with `TArity` args,
                // instantiating
                // a `data_type` object depending on the current iteration.
                return call_with_first_n_args<TArity>(
                    get_fn_wrapper(TDataType{}), FWD(xs)...);
            }

            template <typename TDataType, typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) impl_(
                TDataType, Ts&&... xs)
            {
                // Make sure that the count of loop arguments is divisible
                // by
                // `TArity`.
                VRM_CORE_STATIC_ASSERT_NM(sizeof...(xs) % TArity == 0);

                // TODO: excess argument policy/strategy?
                // * discard
                // * static_assert
                // * fill with <X>

                // Get current metadata.
                // This is the initial metadata "(0, null)" in case of the
                // first
                // iteration.
                using curr_metadata = TDataType;

                auto fn_call = [this, &xs...]() -> decltype(auto)
                {
                    return call_with_arity(curr_metadata{}, FWD(xs)...);
                };

                // "Predict" what the current iteration will return.
                using ret_t = adapt_return_type<decltype(fn_call())>;

                // Call the body of the `static_for`.
                fn_call();

                return static_if(is_break<ret_t>{})
                    .then([&](auto&&...)
                        {
                            return ret_t{};
                        })
                    .else_([&](auto&&... zs)
                        {
                            constexpr auto has_args(sizeof...(zs) > TArity);
                            return static_if(bool_v<has_args>)
                                .then([&](auto&&... ys)
                                    {
                                        return this->continue_<ret_t>(
                                            curr_metadata{}, FWD(ys)...);
                                    })
                                .else_([](auto&&...)
                                    {
                                        return ret_t{};
                                    })(FWD(zs)...);
                        })(FWD(xs)...);
            }

            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs)
            // TODO: noexcept
            {
                // Runs the "static for" by calling the inner implementation
                // function with "zeroth-iteration" metadata.

                // The first metadata has iteration count `0`, arg index `0`
                // and
                // a special type to signal the lack of a previous return
                // type.

                using first_metadata = metadata<0, 0, void_continue_t>;
                return impl_(first_metadata{}, FWD(xs)...);
            }
        };
    }

    template <sz_t TArity = 1, typename TF>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) static_for(TF && f)
    {
        // Returns a callable "static for" wrapper with user-specified
        // arity.

        using decayed_f = std::decay_t<decltype(f)>;
        return impl::static_for_result<TArity, decayed_f>(FWD(f));
    }

    using impl::unwrap;
}
VRM_CORE_NAMESPACE_END

// TODO: please cleanup and comment
