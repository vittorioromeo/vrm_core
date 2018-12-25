// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>

namespace vrm::core
{
    /// @brief If present, removes rvalue referenceness from `T`.
    /// @details Identity case.
    template <typename T>
    struct remove_rvalue_reference
    {
        using type = T;
    };

    /// @brief If present, removes rvalue referenceness from `T`.
    /// @details Rvalue reference removal case.
    template <typename T>
    struct remove_rvalue_reference<T&&>
    {
        using type = T;
    };

    /// @brief If present, removes rvalue referenceness from `T`.
    /// @details Type alias.
    template <typename T>
    using remove_rvalue_reference_t = typename remove_rvalue_reference<T>::type;
}
