// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/internal.hpp>

#if(defined(__linux) || defined(__unix) || defined(__posix) || \
    defined(__LINUX__) || defined(__linux__))
/// @macro This macro is defined if the current OS is Linux.
#define VRM_CORE_OS_LINUX 1
#elif(defined(_WIN64) || defined(_WIN32) || defined(__CYGWIN32__) || \
      defined(__MINGW32__))
/// @macro This macro is defined if the current OS is Windows.
#define VRM_CORE_OS_WINDOWS 1
#elif(defined(MACOSX) || defined(__DARWIN__) || defined(__APPLE__))
/// @macro This macro is defined if the current OS is Mac.
#define VRM_CORE_OS_MAC 1
#else
/// @macro This macro is defined if the current OS is unknown.
#define VRM_CORE_OS_UNKNOWN 1
#endif