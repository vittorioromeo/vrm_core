// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_traits/bool_constant.hpp>

VRM_CORE_NAMESPACE
{
    template <typename TOut, typename TIn>
    using are_both_numbers =
        bool_constant<std::is_arithmetic<TOut>{} && std::is_arithmetic<TIn>() &&
                      !std::is_enum<TOut>() && !std::is_enum<TIn>()>;

    template <typename TOut, typename TIn>
    using same_signedness =
        bool_constant<std::is_signed<TOut>{} == std::is_signed<TIn>{}>;

    template <typename TEnum, typename TOut>
    using underlying_convertible_to = bool_constant<
        std::is_convertible<std::underlying_type_t<TEnum>, TOut>{}>;

    template <typename TOut, typename TIn>
    using number_convertible_to_enum =
        bool_constant<std::is_enum<TOut>() && !std::is_enum<TIn>() &&
                      underlying_convertible_to<TOut, TIn>{}>;

    template <typename TOut, typename TIn>
    using are_both_enums =
        bool_constant<std::is_enum<TOut>() && std::is_enum<TIn>()>;

    template <typename TOut, typename TIn>
    using are_underlying_types_convertible =
        bool_constant<std::is_convertible<std::underlying_type_t<TOut>,
            std::underlying_type_t<TIn>>{}>;

    template <typename TBase, typename TDerived>
    using is_same_or_base_of =
        bool_constant<std::is_same<TBase, TDerived>{} ||
                      std::is_base_of<TBase, TDerived>{}>;

    template <typename TDerived, typename TBase>
    using is_same_or_derived_of = is_same_or_base_of<TBase, TDerived>;

    template <typename T, typename TStorage>
    using valid_storage =
        bool_constant<sizeof(typename TStorage::type) >= sizeof(T) &&
                      alignof(typename TStorage::type) >= alignof(T)>;
}
VRM_CORE_NAMESPACE_END