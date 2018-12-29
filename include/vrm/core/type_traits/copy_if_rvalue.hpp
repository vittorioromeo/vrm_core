// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/type_traits/qualifiers.hpp>
#include <vrm/core/type_traits/remove_rvalue_reference.hpp>
#include <vrm/core/utility_macros.hpp>

// TODO: docs, move, tests

namespace vrm::core
{
    template <typename T>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto copy_if_rvalue(
        T&& x) noexcept(!std::is_rvalue_reference_v<T> ||
                        std::is_nothrow_copy_constructible_v<T>)
        -> remove_rvalue_reference_t<decltype(FWD(x))>
    {
        return FWD(x);
    }
} // namespace vrm::core
