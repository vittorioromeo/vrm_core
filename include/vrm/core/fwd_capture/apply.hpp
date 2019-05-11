// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/fwd_capture/single.hpp>
#include <vrm/core/tuple_utils/apply.hpp>

namespace vrm::core
{
    template <typename TF, typename... TFwdCaptures>
    constexpr decltype(auto) apply_fwd_capture(TF&& f, TFwdCaptures&&... fcs)
    // TODO: noexcept
    {
        return multi_apply(
            [&f](auto&&... xs) -> decltype(
                                   auto) { return FWD(f)(xs.fwd_get()...); },
            FWD(fcs)...);
    }
} // namespace vrm::core
