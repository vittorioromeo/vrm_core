// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp.hpp>
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
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)        // .
            args_call_wrapper(TFArgGetter, TF&& f, Ts&&... xs) // .
            noexcept(
                noexcept(apply(f, std::declval<TFArgGetter>()(FWD(xs)...))))
        {
            return apply(f, TFArgGetter{}(FWD(xs)...));
        }

        template <sz_t TN>
        struct first_n_args_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs) noexcept
            {
                return first_n_args<TN>(FWD(xs)...);
            }
        };

        template <sz_t TN>
        struct last_n_args_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs) noexcept
            {
                return last_n_args<TN>(FWD(xs)...);
            }
        };

        template <sz_t TN>
        struct all_args_from_wrapper
        {
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs) noexcept
            {
                return all_args_from<TN>(FWD(xs)...);
            }
        };
    }
}
VRM_CORE_NAMESPACE_END
