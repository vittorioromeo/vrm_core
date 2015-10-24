// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/type_traits/bool_constant.hpp>

VRM_CORE_NAMESPACE
{
    template <typename TOut, typename TIn>
    using num_convertible =
        bool_constant<std::is_arithmetic<TOut>{} && std::is_arithmetic<TIn>() &&
                      !std::is_enum<TOut>() && !std::is_enum<TIn>()>;

    template <typename TOut, typename TIn>
    using sign_compatible =
        bool_constant<std::is_signed<TOut>{} == std::is_signed<TIn>{}>;

    template <typename TOut, typename TIn>
    using num_convertible_to_enum =
        bool_constant<std::is_enum<TOut>() && !std::is_enum<TIn>() &&
                      std::is_convertible<std::underlying_type_t<TOut>, TIn>{}>;

    template <typename TOut, typename TIn>
    using enum_convertible_to_enum =
        bool_constant<std::is_enum<TOut>() && std::is_enum<TIn>()>;

    template <typename TBase, typename T>
    using is_same_or_base_of =
        bool_constant<std::is_same<TBase, T>{} || std::is_base_of<TBase, T>{}>;

    template <typename T, typename TStorage>
    using valid_storage =
        bool_constant<sizeof(typename TStorage::type) >= sizeof(T) &&
                      alignof(typename TStorage::type) >= alignof(T)>;
}
VRM_CORE_NAMESPACE_END