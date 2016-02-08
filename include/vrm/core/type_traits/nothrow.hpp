// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T, typename... Ts>
    using has_nothrow_call_operator =
        bool_<noexcept((std::declval<T>())(std::declval<Ts>()...))>;
}
VRM_CORE_NAMESPACE_END
