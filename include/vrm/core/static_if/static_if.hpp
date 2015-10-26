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
#include <vrm/core/static_if/impl/static_if_true.hpp>
#include <vrm/core/static_if/impl/static_if_false.hpp>
#include <vrm/core/static_if/impl/static_if_result.hpp>

VRM_CORE_NAMESPACE
{
    template <typename TPredicate>
    VRM_CORE_ALWAYS_INLINE auto static_if(TPredicate) noexcept
    {
        return impl::static_if_<TPredicate{}>{};
    }
}
VRM_CORE_NAMESPACE_END