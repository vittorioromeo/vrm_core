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
            // Thread-safety policies.
            namespace shared_lock_policy
            {
                /// @brief Non-thread-safe policy. No additional performance
                /// overhead.
                struct none
                {
                };

                // TODO: other policies!
            }
        }
    }
}
VRM_CORE_NAMESPACE_END
