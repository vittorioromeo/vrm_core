// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/config/names.hpp>
#include <vrm/core/fwd_capture/single.hpp>
#include <vrm/core/tuple_utils/apply.hpp>

VRM_CORE_NAMESPACE
{
    template <typename TF, typename... TFwdCaptures>
    constexpr decltype(auto) apply_fwd_capture(TF && f, TFwdCaptures && ... fcs)
    // TODO: noexcept
    {
        return multi_apply([&f](auto&&... xs) -> decltype(
                               auto) { return FWD(f)(xs.fwd_get()...); },
            FWD(fcs)...);
    }
}
VRM_CORE_NAMESPACE_END
