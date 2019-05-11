// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/attributes.hpp>
#include <vrm/core/is_valid.hpp>

namespace vrm::core
{
    namespace impl
    {
        VRM_CORE_ALWAYS_INLINE auto VRM_CORE_CONST_FN is_strong_typedef_impl()
        {
            return is_valid(
                [](auto x) -> typename decltype(x)::strong_typedef_tag{});
        }
    } // namespace impl

    template <typename T>
    constexpr auto is_strong_typedef_v = // .
        decltype(impl::is_strong_typedef_impl()(T{})){};
} // namespace vrm::core
