// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <utility>
#include <vrm/core/internal.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

// Implemented thanks to Daniel Frey:
// http://stackoverflow.com/a/29901074/598696

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename, typename>
        struct for_args_helper;

        template <std::size_t... Bs, std::size_t... Cs>
        struct for_args_helper<std::index_sequence<Bs...>,
            std::index_sequence<Cs...>>
        {
            using swallow = bool[];

#define IMPL_IMPL_FORNARGS_EXECN_BODY() f(std::get<TArity + Cs>(FWD(xs))...)

            template <std::size_t TArity, typename TF, typename TTpl,
                typename... Ts>
            VRM_CORE_ALWAYS_INLINE static constexpr void exec_n(TF&& f,
                TTpl&& xs) noexcept(noexcept(IMPL_IMPL_FORNARGS_EXECN_BODY()))
            {
                IMPL_IMPL_FORNARGS_EXECN_BODY();
            }

#undef IMPL_IMPL_FORNARGS_EXECN_BODY

#define IMPL_IMPL_FORNARGS_EXEC_BODY() \
    (void) swallow { (exec_n<(Bs * sizeof...(Cs))>(f, FWD(xs)), true)..., true }

            template <typename TF, typename TTpl, typename... Ts>
            VRM_CORE_ALWAYS_INLINE static constexpr void exec(TF&& f,
                TTpl&& xs) noexcept(noexcept(IMPL_IMPL_FORNARGS_EXEC_BODY()))
            {
                IMPL_IMPL_FORNARGS_EXEC_BODY();
            }

#undef IMPL_IMPL_FORNARGS_EXEC_BODY
        };


#define IMPL_FORNARGS_BODY()                                                \
    impl::for_args_helper<std::make_index_sequence<sizeof...(Ts) / TArity>, \
        std::make_index_sequence<TArity>>::exec(FWD(f),                     \
        std::forward_as_tuple(FWD(xs)...))

        template <std::size_t TArity>
        struct for_args_dispatch
        {
            template <typename TF, typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr static void exec(
                TF&& f, Ts&&... xs) noexcept(noexcept(IMPL_FORNARGS_BODY()))
            {
                VRM_CORE_STATIC_ASSERT(
                    TArity > 0, "Unallowed arity: must be greater than 0");

                VRM_CORE_STATIC_ASSERT(sizeof...(Ts) % TArity == 0,
                    "Unallowed arity: not divisible by number of arguments");

                IMPL_FORNARGS_BODY();
            }
        };

#undef IMPL_FORNARGS_BODY

        template <>
        struct for_args_dispatch<1>
        {
            template <typename TF, typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr static void exec(
                TF&& f, Ts&&... xs) // .
                noexcept(noexcept(
                    (void)(std::initializer_list<int>{(f(FWD(xs)), 0)...})))
            {
                using swallow = std::initializer_list<int>;
                return (void)(swallow{(f(FWD(xs)), 0)...});
            }
        };
    }

    template <std::size_t TArity = 1, typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE                             // .
        constexpr void for_args(TF && f, Ts && ... xs) // .
        noexcept(
            noexcept(impl::for_args_dispatch<TArity>::exec(FWD(f), FWD(xs)...)))
    {
        impl::for_args_dispatch<TArity>::exec(FWD(f), FWD(xs)...);
    }
}
VRM_CORE_NAMESPACE_END