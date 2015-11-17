// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <utility>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto decay_tuple_size() noexcept
    {
        return std::tuple_size<std::decay_t<T>>{};
    }

    template <typename T>
    using make_tuple_index_sequence =
        std::make_index_sequence<decay_tuple_size<T>()>;
}
VRM_CORE_NAMESPACE_END
