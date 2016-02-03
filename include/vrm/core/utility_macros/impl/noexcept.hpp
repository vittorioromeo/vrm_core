// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/utils.hpp>
#include <vrm/pp/cat.hpp>

/// @brief Expands to both the `noexcept` and body of a function.
/// @details The `return` keyword is automatically added before the variadic
/// arguments.
#define VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY_VA(...) \
    noexcept(noexcept(VRM_PP_EXPAND(__VA_ARGS__)))     \
    {                                                  \
        return VRM_PP_EXPAND(__VA_ARGS__);             \
    }

/// @brief Expands to both the `noexcept` and body of a function.
/// @details The `return` keyword is automatically added before the variadic
/// arguments. The contents are expanded through the `VRM_CORE_IMPL_BODY()`
/// macro.
#define VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY() \
    VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY_VA(VRM_CORE_IMPL_BODY())
