// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <type_traits>
#include <vrm/core/utility_macros.hpp>

namespace vrm::core
{
    template <typename... Ts>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto make_array(
        Ts&&... xs) // .
        VRM_CORE_RETURNS(
            std::array<std::decay_t<std::common_type_t<Ts...>>, sizeof...(Ts)>{
                {FWD(xs)...}})
}

#undef VRM_CORE_IMPL_BODY
