// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>

VRM_CORE_NAMESPACE
{
    template <typename TOut, typename TIn>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) self_cast(TIn && x) noexcept
    {
        using out_decay = std::decay_t<TOut>;
        using in_decay = std::decay_t<TIn>;

        VRM_CORE_STATIC_ASSERT_NM(std::is_same<out_decay, in_decay>{});

        return static_cast<TOut>(FWD(x));
    }
}
VRM_CORE_NAMESPACE_END
