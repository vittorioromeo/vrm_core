// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/for_args/for_args_data.hpp>

namespace vrm::core
{
    namespace impl
    {
        // Only for the conditional `noexcept`... meh.
        template <typename TF>
        struct ignore_first_arg
        {
            TF _f;

            template <typename T>
            ignore_first_arg(T&& f) noexcept : _f{f}
            {
            }

            template <typename T, typename... Ts>
            VRM_CORE_ALWAYS_INLINE void operator()(T&&, Ts&&... xs)
            {
                _f(FWD(xs)...);
            }
        };
    }

    template <sz_t TArity = 1, typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE                             // .
        constexpr void for_args(TF && f, Ts && ... xs) // .
        noexcept(noexcept(for_args_data<TArity>(
            impl::ignore_first_arg<decltype(f)>{f}, FWD(xs)...)))
    {
        for_args_data<TArity>(
            [&f](auto, auto&&... rest)
            {
                f(FWD(rest)...);
            },
            FWD(xs)...);
    }
}
