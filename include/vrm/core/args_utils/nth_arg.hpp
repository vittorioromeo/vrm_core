// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/tuple_utils/ref_tuple.hpp>

VRM_CORE_NAMESPACE
{
    template <std::size_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) nth_arg(
        Ts && ... xs) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(sizeof...(xs) > TN);

        using nth_arg_type =
            std::tuple_element_t<TN, decltype(make_ref_tpl(FWD(xs)...))>;

        return static_cast<nth_arg_type>(
            FWD(std::get<TN>(make_ref_tpl(FWD(xs)...))));
    }
}
VRM_CORE_NAMESPACE_END