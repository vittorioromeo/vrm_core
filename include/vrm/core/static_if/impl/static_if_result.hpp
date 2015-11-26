// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

// Adapted from:
// https://github.com/isocpp/CppCoreGuidelines/issues/353

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/casts/polymorphic.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TFunctionToCall>
        struct static_if_result : TFunctionToCall
        {
            template <typename TFFwd>
            VRM_CORE_ALWAYS_INLINE constexpr static_if_result(
                TFFwd&& f) noexcept : TFunctionToCall(FWD(f))
            {
            }

            template <typename TF>
            VRM_CORE_ALWAYS_INLINE constexpr auto& else_(TF&&) noexcept
            {
                // Ignore everything, we found a result.
                return *this;
            }

            template <typename TF>
            VRM_CORE_ALWAYS_INLINE constexpr auto& then(TF&&) noexcept
            {
                // Ignore everything, we found a result.
                return *this;
            }

            template <typename TPredicate>
            VRM_CORE_ALWAYS_INLINE constexpr auto& else_if(TPredicate) noexcept
            {
                // Ignore everything, we found a result.
                return *this;
            }

            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
                Ts&&... xs)
            // TODO: g++ pls
            // noexcept(noexcept(to_base<TFunctionToCall> (*this)(FWD(xs)...)))
            {
                // TODO: can this be constexpr?
                return to_base<TFunctionToCall> (*this)(FWD(xs)...);
            }
        };

        template <typename TF>
        VRM_CORE_ALWAYS_INLINE constexpr auto make_static_if_result(
            TF&& f) noexcept
        {
            return static_if_result<TF>{FWD(f)};
        }
    }
}
VRM_CORE_NAMESPACE_END
