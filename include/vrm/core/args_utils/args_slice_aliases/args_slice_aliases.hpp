// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

namespace vrm::core
{
    /// @brief Returns the slice `[..., TN)`.
    template <sz_t TN, typename... Ts>
    constexpr auto first_n_args(Ts&&... xs) noexcept;

    /// @brief Returns the slice `(TN, ...]`.
    template <sz_t TN, typename... Ts>
    constexpr auto last_n_args(Ts&&... xs) noexcept;

    /// @brief Returns the slice `[TN, ...]`.
    /// /// @details Includes `TN`.
    template <sz_t TN, typename... Ts>
    constexpr auto all_args_from(Ts&&... xs) noexcept;

    /// @brief Returns the slice `(TN, ...]`.
    /// @details Excludes `TN`.
    template <sz_t TN, typename... Ts>
    constexpr auto all_args_after(Ts&&... xs) noexcept;

    /// @brief Returns the slice `[..., TN]`.
    /// @details Includes `TN`.
    template <sz_t TN, typename... Ts>
    constexpr auto all_args_until(Ts&&... xs) noexcept;

    /// @brief Returns the slice `[..., TN)`.
    /// @details Excludes `TN`.
    template <sz_t TN, typename... Ts>
    constexpr auto all_args_before(Ts&&... xs) noexcept;

    /// @brief Returns the first argument of a variadic pack.
    template <typename... Ts>
    constexpr decltype(auto) first_arg(Ts&&... xs) noexcept;

    /// @brief Returns the last argument of a variadic pack.
    template <typename... Ts>
    constexpr decltype(auto) last_arg(Ts&&... xs) noexcept;
} // namespace vrm::core
