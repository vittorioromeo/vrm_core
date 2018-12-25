// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#if defined(__cpp_rtti) || defined(__GXX_RTTI) || defined(_CPPRTTI)
/// @macro This macro is defined if RTTI is enabled.
#define VRM_CORE_RTTI_ENABLED 1
#else
/// @macro This macro is defined if RTTI is disabled.
#define VRM_CORE_RTTI_DISABLED 1
#endif
