// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp/cat.hpp>
#include <vrm/pp/utils.hpp>

/// @brief Expands to the body of a function.
/// @details The `return` keyword is automatically added before the variadic
/// arguments.
#define VRM_CORE_RETURNS_BODY(...) \
    {                              \
        return __VA_ARGS__;        \
    }

/// @brief Expands to the `noexcept` clause and the trailing return type of a
/// function.
#define VRM_CORE_NOEXCEPT_AND_TRT(...) \
    noexcept(noexcept(__VA_ARGS__))->decltype(__VA_ARGS__)

/// @brief Expands to the body, the `noexcept` clause, and the trailing return
/// type of a function.
/// @details The `return` keyword is automatically added before the variadic
/// arguments.
#define VRM_CORE_RETURNS(...) \
    VRM_CORE_NOEXCEPT_AND_TRT(__VA_ARGS__) VRM_CORE_RETURNS_BODY(__VA_ARGS__)
