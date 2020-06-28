// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/type_aliases.hpp>

#include <type_traits>
#include <utility>

namespace vrm::core
{
    template <typename TOut, typename TIn>
    using same_signedness =
        bool_<std::is_signed_v<TOut> == std::is_signed_v<TIn>>;

    template <typename TEnum, typename TOut>
    using underlying_convertible_to =
        bool_<std::is_convertible_v<std::underlying_type_t<TEnum>, TOut>>;

    template <typename TOut, typename TIn>
    using number_convertible_to_enum =
        bool_<std::is_enum_v<TOut> && !std::is_enum_v<TIn> &&
              underlying_convertible_to<TOut, TIn>{}>;

    template <typename TOut, typename TIn>
    using are_both_enums = bool_<std::is_enum_v<TOut> && std::is_enum_v<TIn>>;

    template <typename TOut, typename TIn>
    using are_underlying_types_convertible =
        bool_<std::is_convertible_v<std::underlying_type_t<TOut>,
            std::underlying_type_t<TIn>>>;

    template <typename T, typename TStorage>
    using valid_storage = bool_<sizeof(typename TStorage::type) >= sizeof(T) &&
                                alignof(typename TStorage::type) >= alignof(T)>;
} // namespace vrm::core
