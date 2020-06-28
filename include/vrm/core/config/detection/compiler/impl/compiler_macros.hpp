// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#if defined(__clang__)
/// @macro This macro is defined if the current compiler is clang.
#define VRM_CORE_COMPILER_CLANG 1
#elif defined(__GNUC__)
/// @macro This macro is defined if the current compiler is gcc.
#define VRM_CORE_COMPILER_GCC 1
#elif defined(_MSC_VER)
/// @macro This macro is defined if the current compiler is MSVC.
#define VRM_CORE_COMPILER_MSVC 1
#else
/// @macro This macro is defined if the current compiler is unknown.
#define VRM_CORE_COMPILER_UNKNOWN 1
#endif
