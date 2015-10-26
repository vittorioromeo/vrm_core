// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <bool TPredicateResult>
        struct static_if_;

        template <typename TPredicate>
        VRM_CORE_ALWAYS_INLINE auto make_static_if(TPredicate) noexcept
        {
            return static_if_<TPredicate{}>{};
        }
    }
}
VRM_CORE_NAMESPACE_END