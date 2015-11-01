// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>

VRM_CORE_NAMESPACE
{
    template <std::size_t TV>
    using size_t_constant = std::integral_constant<std::size_t, TV>;

    template <std::size_t TV>
    using size_t_ = size_t_constant<TV>;
}
VRM_CORE_NAMESPACE_END