// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

// TODO: make these functions, not macros

#include <vrm/core/config.hpp>

#if defined(VRM_CORE_COMPILER_CLANG) || defined(VRM_CORE_COMPILER_GCC)

/// @macro Micro-optimization telling the compiler that this condition is more
/// likely to happen than the `else` branch.
#define VRM_CORE_LIKELY(...) __builtin_expect(!!(__VA_ARGS__), 1)

/// @macro Micro-optimization telling the compiler that this condition is less
/// likely to happen than the `else` branch.
#define VRM_CORE_UNLIKELY(...) __builtin_expect(!!(__VA_ARGS__), 0)

#else

#define VRM_CORE_LIKELY(...) __VA_ARGS__
#define VRM_CORE_UNLIKELY(...) __VA_ARGS__

#endif
