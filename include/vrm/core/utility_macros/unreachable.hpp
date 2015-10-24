// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cassert>
#include <cstdlib>
#include <vrm/core/config.hpp>

#if defined(VRM_CORE_COMPILER_CLANG) || defined(VRM_CORE_COMPILER_GCC)
/// @macro Unreachable code. Uses `__builtin_unreachable`.
/// Requires semicolon at the end.
#define VRM_CORE_UNREACHABLE() __builtin_unreachable()
#else
/// @macro Unreachable code. Uses an assert and `exit(EXIT_FAILURE);`.
/// Requires semicolon at the end.
#define VRM_CORE_UNREACHABLE() \
    do                         \
    {                          \
        assert(false);         \
        exit(EXIT_FAILURE);    \
    } while(false)
#endif