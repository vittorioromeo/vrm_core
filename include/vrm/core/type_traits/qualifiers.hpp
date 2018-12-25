// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/type_aliases.hpp>

namespace vrm::core
{
    template <typename T, typename TSource>
    using copy_const_qualifier =
        std::conditional_t<std::is_const<TSource>{}, // .
            std::add_const_t<T>, T>;

    template <typename T, typename TSource>
    using copy_volatile_qualifier =
        std::conditional_t<std::is_volatile<TSource>{}, // .
            std::add_volatile_t<T>, T>;

    template <typename T, typename TSource>
    using copy_cv_qualifiers =
        copy_const_qualifier<copy_volatile_qualifier<T, TSource>, TSource>;
}
