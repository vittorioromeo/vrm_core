// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

// TODO: (temporary)
#define VRM_CORE_INLINE_LIBRARY 1



#if defined(VRM_CORE_INLINE_LIBRARY)

/// @macro Use as an header-only library.
#define VRM_CORE_FN_API inline
#define VRM_CORE_CLASS_API

/// @macro Use as a statically-linked library.
#elif defined(VRM_CORE_STATIC_LIBRARY)

#define VRM_CORE_FN_API
#define VRM_CORE_CLASS_API

/// @macro Use as an exported DLL.
#elif defined(VRM_CORE_EXPORT_LIBRARY)

#define VRM_CORE_FN_API __declspec(dllexport)
#define VRM_CORE_CLASS_API __declspec(dllexport)

#elif defined(VRM_CORE_IMPORT_LIBRARY)

/// @macro Use as an imported DLL.
#define VRM_CORE_FN_API __declspec(dllimport)
#define VRM_CORE_CLASS_API __declspec(dllimport)

#endif
