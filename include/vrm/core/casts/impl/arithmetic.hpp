// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/strong_typedef.hpp>
#include <vrm/core/casts/impl/overflow_check.hpp>

VRM_CORE_NAMESPACE
{
    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr auto to_num(const TIn& x) noexcept
    {
        VRM_CORE_STATIC_ASSERT( // .
            std::is_arithmetic<underlying_if_strong_typedef_type<TOut>>{},
            "`TOut` output type must be an arithmetic type.");

        VRM_CORE_STATIC_ASSERT( // .
            std::is_arithmetic<underlying_if_strong_typedef_type<TIn>>{},
            "`TIn` input type must be an arithmetic type.");

        VRM_CORE_CONSTEXPR_ASSERT((!impl::will_overflow<TOut, TIn>(x)));

        return static_cast<TOut>(x);
    }
}
VRM_CORE_NAMESPACE_END
