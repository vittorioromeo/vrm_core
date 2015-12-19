// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>

#if defined(__clang__)
/// @macro This macro is defined if the current compiler is clang.
#define VRM_CORE_COMPILER_CLANG 1
#elif defined(__GNUC__)
/// @macro This macro is defined if the current compiler is gcc.
#define VRM_CORE_COMPILER_GCC 1
#elif defined(_MSC_VER)
/// @macro This macro is defined if the current compiler is MSCV.
#define VRM_CORE_COMPILER_MSCV 1
#else
/// @macro This macro is defined if the current compiler is unknown.
#define VRM_CORE_COMPILER_UNKNOWN 1
#endif