// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

namespace vrm::core::resource::impl
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
    } // namespace shared_lock_policy
} // namespace vrm::core::resource::impl
