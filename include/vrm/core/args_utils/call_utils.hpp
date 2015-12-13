// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/tuple_utils/apply.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>
#include <vrm/core/args_utils/args_slice.hpp>
#include <vrm/core/args_utils/args_slice_aliases.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TFArgGetter, typename TF, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
            args_call_wrapper(TFArgGetter, TF&& f, Ts&&... xs)
        {
            return apply(f, TFArgGetter{}(FWD(xs)...));
        }

        template <sz_t TN>
        struct first_n_args_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs)
            {
                return first_n_args<TN>(FWD(xs)...);
            }
        };

        template <sz_t TN>
        struct last_n_args_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs)
            {
                return last_n_args<TN>(FWD(xs)...);
            }
        };

        template <sz_t TN>
        struct all_args_from_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs)
            {
                return all_args_from<TN>(FWD(xs)...);
            }
        };
    }

    template <sz_t TN, typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        call_with_first_n_args(TF && f, Ts && ... xs)
    {
        return impl::args_call_wrapper(
            impl::first_n_args_wrapper<TN>{}, FWD(f), FWD(xs)...);
    }

    template <sz_t TN, typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        call_with_last_n_args(TF && f, Ts && ... xs)
    {
        return impl::args_call_wrapper(
            impl::last_n_args_wrapper<TN>{}, FWD(f), FWD(xs)...);
    }

    template <sz_t TN, typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        call_with_all_args_from(TF && f, Ts && ... xs)
    {
        return impl::args_call_wrapper(
            impl::all_args_from_wrapper<TN>{}, FWD(f), FWD(xs)...);
    }
}
VRM_CORE_NAMESPACE_END

// TODO: noexcept
