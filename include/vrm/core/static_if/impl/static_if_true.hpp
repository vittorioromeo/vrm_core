// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

// Adapted from:
// https://github.com/isocpp/CppCoreGuidelines/issues/353

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/static_if/impl/static_if_impl.hpp>
#include <vrm/core/static_if/impl/static_if_result.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <>
        struct static_if_<true> final
        {
            template <typename TF>
            VRM_CORE_ALWAYS_INLINE constexpr auto& else_(TF&&) noexcept
            {
                // Ignore `else_`, as the predicate is true.
                return *this;
            }

            template <typename TF>
            VRM_CORE_ALWAYS_INLINE constexpr auto then(TF&& f) noexcept
            {
                // We found a matching branch, just make a result and ignore
                // everything else.
                return make_static_if_result(FWD(f));
            }

            template <typename TPredicate>
            VRM_CORE_ALWAYS_INLINE constexpr auto& else_if(TPredicate) noexcept
            {
                // Ignore `else_if`, as the predicate is true.
                return *this;
            }
        };
    }
}
VRM_CORE_NAMESPACE_END
