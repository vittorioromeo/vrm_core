// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>

#if defined(_LIBCPP_VERSION)
#define VRM_CORE_STDLIB_LIBCXX 1
#elif defined(__GLIBCXX__)
#define VRM_CORE_STDLIB_LIBSTDCXX 1
#else
#define VRM_CORE_STDLIB_UNKNOWN 1
#endif