// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>
#include <vrm/core/config.hpp>

// `VRM_CORE_ASSERT_FORCE_OFF` and `VRM_CORE_ASSERT_FORCE_ON` macros force
// enabling/disabling of assertions.
// `VRM_CORE_ASSERT_FORCE_ON` has priority over `VRM_CORE_ASSERT_FORCE_OFF`.

#if(defined(VRM_CORE_ASSERT_FORCE_OFF) || !defined(VRM_CORE_DEBUG)) && \
    !defined(VRM_CORE_ASSERT_FORCE_ON)
#define VRM_CORE_IMPL_ASSERT_DISABLED 1
#else
#define VRM_CORE_IMPL_ASSERT_DISABLED 0
#endif

#if VRM_CORE_IMPL_ASSERT_DISABLED
#include <vrm/core/assert/impl/assert_macros_disabled.hpp>
#else
#include <vrm/core/assert/impl/assert_macros_enabled.hpp>
#endif
