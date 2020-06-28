// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#if defined(__unix__) || defined(__unix)

// ---
#if defined(__ANDROID__)
/// @macro This macro is defined if the current OS is Android.
#define VRM_CORE_OS_ANDROID 1
#elif defined(__linux__)
/// @macro This macro is defined if the current OS is Linux.
#define VRM_CORE_OS_LINUX 1
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
/// @macro This macro is defined if the current OS is FreeBSD.
#define VRM_CORE_OS_FREEBSD 1
#endif
// ---

#elif defined(_WIN64) || defined(_WIN32) || defined(__CYGWIN32__) || \
    defined(__MINGW32__)

/// @macro This macro is defined if the current OS is Windows.
#define VRM_CORE_OS_WINDOWS 1

#elif defined(MACOSX) || defined(__DARWIN__) || defined(__APPLE__)

/// @macro This macro is defined if the current OS is Mac.
#define VRM_CORE_OS_MAC 1

#else

/// @macro This macro is defined if the current OS is unknown.
#define VRM_CORE_OS_UNKNOWN 1

#endif
