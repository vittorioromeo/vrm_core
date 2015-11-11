// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cstddef>
#include <type_traits>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

VRM_CORE_NAMESPACE
{
    template <bool TV>
    using bool_constant = std::integral_constant<bool, TV>;

    template <bool TV>
    using bool_ = bool_constant<TV>;



    template <long long TV>
    using llong_constant = std::integral_constant<long long, TV>;

    template <long long TV>
    using llong_ = llong_constant<TV>;



    template <sz_t TV>
    using sz_t_constant = std::integral_constant<sz_t, TV>;

    template <sz_t TV>
    using sz_t_ = sz_t_constant<TV>;
}
VRM_CORE_NAMESPACE_END
