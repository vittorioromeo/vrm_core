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
    /// @brief Creates a tuple of values and l-value references.
    /// @details L-values are taken as l-value references inside the tuple.
    /// R-values are copies as values inside the tuple.
    /// @code
    /// int lv{0};
    /// auto t(make_ref_tuple(lv, 0));
    /// // tuple_element_t<0>(t) is int&
    /// // tuple_element_t<1>(t) is int
    /// @endcode
    template <typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) make_ref_tuple(
        Ts && ... xs) noexcept
    {
        return std::tuple<Ts...>(FWD(xs)...);
    }
}
VRM_CORE_NAMESPACE_END
