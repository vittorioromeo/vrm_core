// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/type_traits.hpp>
#include <vrm/core/type_aliases.hpp>
#include <vrm/core/config/names.hpp>
#include <vrm/core/strong_typedef/is_strong_typedef.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename, typename>
        struct underyling_if_strong_typedef_dispatch;

        template <typename T>
        struct underyling_if_strong_typedef_dispatch<T, std::true_type>
        {
            using type = typename T::underlying_type;
        };

        template <typename T>
        struct underyling_if_strong_typedef_dispatch<T, std::false_type>
        {
            using type = T;
        };
    }

    /// @brief Returns `T` if `T` is not a strong typedef, `typename
    /// T::underlying_type` otherwise.
    template <typename T>
    using underlying_if_strong_typedef_type =
        typename impl::underyling_if_strong_typedef_dispatch<T,
            bool_<is_strong_typedef_v<T>>>::type;
}
VRM_CORE_NAMESPACE_END
