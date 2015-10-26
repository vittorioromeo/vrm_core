// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>

VRM_CORE_NAMESPACE
{
    template <bool TV>
    using bool_constant = std::integral_constant<bool, TV>;
}
VRM_CORE_NAMESPACE_END