// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros.hpp>

VRM_CORE_NAMESPACE
{
    template <typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) make_ref_tpl(
        Ts && ... xs) noexcept
    {
        return std::tuple<Ts...>(FWD(xs)...);
    }
}
VRM_CORE_NAMESPACE_END