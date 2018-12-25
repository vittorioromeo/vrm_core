// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/assert.hpp>
#include <vrm/core/casts/impl/overflow_check.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/strong_typedef.hpp>

namespace vrm::core
{
    template <typename TOut, typename TIn>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto to_num(
        const TIn& x) noexcept
    {
        static_assert( // .
            std::is_arithmetic_v<underlying_if_strong_typedef_type<TOut>>,
            "`TOut` output type must be an arithmetic type.");

        static_assert( // .
            std::is_arithmetic_v<underlying_if_strong_typedef_type<TIn>>,
            "`TIn` input type must be an arithmetic type.");

        VRM_CORE_CONSTEXPR_ASSERT((!impl::will_overflow<TOut, TIn>(x)));

        return static_cast<TOut>(x);
    }
} // namespace vrm::core
