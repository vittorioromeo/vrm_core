// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

// Adapted from:
// https://github.com/isocpp/CppCoreGuidelines/issues/353

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TFunctionToCall>
        class static_if_result
        {
        private:
            TFunctionToCall _f;

        public:
            template <typename TFFwd>
            VRM_CORE_ALWAYS_INLINE static_if_result(TFFwd&& f) noexcept
                : _f(FWD(f))
            {
            }

            template <typename TF>
            VRM_CORE_ALWAYS_INLINE auto& else_(TF&&) noexcept
            {
                // Ignore everything, we found a result.

                return *this;
            }

            template <typename TF>
            VRM_CORE_ALWAYS_INLINE auto& then(TF&&) noexcept
            {
                // Ignore everything, we found a result.

                return *this;
            }

            template <typename TPredicate>
            VRM_CORE_ALWAYS_INLINE auto& else_if(TPredicate) noexcept
            {
                // Ignore everything, we found a result.

                return *this;
            }

            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE decltype(auto) operator()(
                Ts&&... xs) noexcept(noexcept(_f(FWD(xs)...)))
            {
                return _f(FWD(xs)...);
            }
        };

        template <typename TF>
        VRM_CORE_ALWAYS_INLINE auto make_static_if_result(TF&& f) noexcept
        {
            return static_if_result<decltype(f)>{FWD(f)};
        }
    }
}
VRM_CORE_NAMESPACE_END