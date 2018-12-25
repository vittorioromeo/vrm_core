// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <utility>

#define VRM_CORE_FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

#if !defined(VRM_CORE_NO_FWD_MACRO) && !defined(FWD)
#define FWD VRM_CORE_FWD
#endif
