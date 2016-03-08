// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>

VRM_CORE_NAMESPACE
{
    template <typename>
    struct is_strong_typedef : std::false_type
    {
    };

    template <typename T>
    constexpr bool is_strong_typedef_v = is_strong_typedef<T>::value;
}
VRM_CORE_NAMESPACE_END
