// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#define VRM_CORE_NAMESPACE \
    namespace vrm          \
    {                      \
    namespace core

#define VRM_CORE_NAMESPACE_END }

#define VRM_CORE_ALWAYS_INLINE __attribute__((always_inline)) inline

#define VRM_CORE_INLINE_LIBRARY 1

#if defined(VRM_CORE_INLINE_LIBRARY)
#define VRM_CORE_API inline
#elif defined(VRM_CORE_STATIC_LIBRARY)
#define VRM_CORE_API
#elif defined(VRM_CORE_EXPORT_LIBRARY)
#define VRM_CORE_API __declspec(dllexport)
#elif defined(VRM_CORE_IMPORT_LIBRARY)
#define VRM_CORE_API __declspec(dllimport)
#endif
