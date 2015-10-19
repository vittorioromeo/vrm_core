// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>
#include <vrm/core/detection.hpp>

/// @macro Static assertion. Checked at compile-time.
/// @details Wrapper for the standard `static_assert`.
#define VRM_CORE_STATIC_ASSERT(...) static_assert(__VA_ARGS__)

/// @macro Static assertion. Checked at compile-time. No message.
/// @details Wrapper for the standard `static_assert` with a default message.
#define VRM_CORE_STATIC_ASSERT_NM(...) \
    static_assert(__VA_ARGS__, VRM_PP_TOSTR(__VA_ARGS__))

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
#include <vrm/core/assert/assert_macros_disabled.hpp>
#else
#include <vrm/core/assert/assert_macros_enabled.hpp>
#endif

// TODO:
// * check ssvu code
// * think about constexpr assertions
// * expression parsing for assertions
// * maybe output to string for tests?