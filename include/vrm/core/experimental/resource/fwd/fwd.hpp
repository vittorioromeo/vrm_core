// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            // Forward declarations.
            template <typename TBehavior, typename TLockPolicy>
            class weak;

            template <typename TBehavior, typename TLockPolicy>
            class shared;
        }
    }
}
VRM_CORE_NAMESPACE_END
