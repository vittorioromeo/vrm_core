// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <type_traits>
#include <vrm/core/value_wrapper.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Wrapper around `T` that has either value or reference semantics
    /// depending on the nature of `T`.
    /// @details The wrapper has reference semantics when `T` is an lvalue
    /// reference. The wrapper has value semantics when `T` is either a value or
    /// an rvalue reference.
    template <typename T>
    using perfect_wrapper = std::conditional_t<             // .
        std::is_lvalue_reference<T>::value,                 // .
        std::reference_wrapper<std::remove_reference_t<T>>, // .
        vrm::core::value_wrapper<T>                         // .
        >;
}
VRM_CORE_NAMESPACE_END
