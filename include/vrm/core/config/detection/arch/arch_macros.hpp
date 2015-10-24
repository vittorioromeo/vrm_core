// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>

#if(defined(WIN_32) || defined(__i386__) || defined(i386) || defined(__x86__))
/// @macro This macro is defined if the current architecture is 32 bit.
#define VRM_CORE_ARCH_32 1
#elif(defined(__amd64) || defined(__amd64__) || defined(__x86_64) || \
      defined(__x86_64__) || defined(_M_X64) || defined(__ia64__) || \
      defined(_M_IA64))
/// @macro This macro is defined if the current architecture is 64 bit.
#define VRM_CORE_ARCH_64 1
#else
/// @macro This macro is defined if the current architecture is unknown.
#define VRM_CORE_ARCH_UNKNOWN 1
#endif