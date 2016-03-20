// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>
#include <vrm/core/is_valid.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        auto VRM_CORE_CONST_FN is_strong_typedef_impl()
        {
            return is_valid([](auto x) ->
                typename decltype(x)::strong_typedef_tag{});
        }
    }

    template <typename T>
    constexpr auto is_strong_typedef_v = // .
        decltype(impl::is_strong_typedef_impl()(T{})){};
}
VRM_CORE_NAMESPACE_END
