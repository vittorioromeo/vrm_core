// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <utility>

#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits.hpp>
#include <vrm/core/static_if.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

// Implemented thanks to Daniel Frey:
// http://stackoverflow.com/a/29901074/598696

// TODO: cleanup with cppcon2015 implementation
// TODO: short circuiting with static_if
// TODO: return value
/*
struct for_args_continue{};
       struct for_args_break{};
       struct for_args_return{};*/

VRM_CORE_NAMESPACE
{
    struct break_t
    {
    };
    struct continue_t
    {
    };

    template <std::size_t TIteration>
    struct static_for_args_data_type
    {
        static constexpr std::size_t iteration{TIteration};
    };

    namespace impl
    {
        template <std::size_t TArity, typename TFunctionToCall>
        struct static_for_args_result
        {
            TFunctionToCall _f;

            template <typename TFFwd>
            VRM_CORE_ALWAYS_INLINE static_for_args_result(TFFwd&& f) noexcept
                : _f(FWD(f))
            {
            }

            template <std::size_t TBegin, typename TF, std::size_t... TIdxs,
                typename... Ts>
            VRM_CORE_ALWAYS_INLINE decltype(auto) call_with_n_no_iteration(
                TF&& f, std::index_sequence<TIdxs...>, Ts&&... xs)
            {
                auto t(std::forward_as_tuple(FWD(xs)...));
                return f(FWD(std::get<TBegin + TIdxs>(t))...);
            }

            template <std::size_t TIteration, std::size_t TBegin, typename TF,
                std::size_t... TIdxs, typename... Ts>
            VRM_CORE_ALWAYS_INLINE decltype(auto) call_with_n(
                TF&& f, std::index_sequence<TIdxs...>, Ts&&... xs)
            {
                auto t(std::forward_as_tuple(FWD(xs)...));
                static_for_args_data_type<TIteration> data{};

                return f(data, FWD(std::get<TBegin + TIdxs>(t))...);
            }

// TODO:
// continue_t -> `skip_next<N = 1> `

            template <std::size_t TNextIteration, typename... Ts>
            VRM_CORE_ALWAYS_INLINE decltype(auto) continue_(Ts&&... xs)
            {
                auto to_call = [this](auto&&... vs)
                {
                    this->impl_<TNextIteration>(FWD(vs)...);
                };

                constexpr auto seq_n(sizeof...(xs)-TArity);

                call_with_n_no_iteration<TArity>(
                    to_call, std::make_index_sequence<seq_n>(), FWD(xs)...);
            }

            template <std::size_t TIteration, typename... Ts>
            VRM_CORE_ALWAYS_INLINE decltype(auto) call_with_arity(Ts&&... xs)
            {
                return call_with_n<TIteration, 0>(
                    _f, std::make_index_sequence<TArity>(), FWD(xs)...);
            }

            template <std::size_t TIteration, typename... Ts>
            VRM_CORE_ALWAYS_INLINE decltype(auto) impl_(Ts&&... xs)
            {
                // Make sure that the count of loop arguments is divisible by
                // `TArity`.
                VRM_CORE_STATIC_ASSERT_NM(sizeof...(xs) % TArity == 0);

                // Get the return type of the current iteration.
                using ret_t = decltype(call_with_arity<TIteration>(FWD(xs)...));

                // Aliases.
                using is_break = std::is_same<ret_t, break_t>;
                using is_continue = std::is_same<ret_t, continue_t>;

                if(is_break{}) return;

                if(!is_continue{})
                {
                    call_with_arity<TIteration>(FWD(xs)...);
                }

                constexpr auto has_args(sizeof...(xs) > TArity);
                static_if(bool_<has_args>{})
                    .then([&](auto&&... ys)
                        {
                            continue_<TIteration + 1>(FWD(ys)...);
                        })(FWD(xs)...);
            }

            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE decltype(auto) operator()(Ts&&... xs)
            {
                impl_<0>(FWD(xs)...);
            }
        };
    }

    template <std::size_t TArity = 1, typename TF>
    VRM_CORE_ALWAYS_INLINE decltype(auto) static_for_args(TF && f)
    {
        return impl::static_for_args_result<TArity, decltype(f)>(FWD(f));
    }
}
VRM_CORE_NAMESPACE_END