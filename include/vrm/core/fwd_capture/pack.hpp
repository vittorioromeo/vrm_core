// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/fwd_capture/single.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <typename... Ts>
        constexpr auto fwd_capture_pack(Ts&&... xs) noexcept(
            noexcept(std::make_tuple(VRM_CORE_FWD_CAPTURE(xs)...)))
        {
            return std::make_tuple(VRM_CORE_FWD_CAPTURE(xs)...);
        }

        template <typename... Ts>
        constexpr auto fwd_copy_capture_pack(Ts&&... xs) noexcept(
            noexcept(std::make_tuple(VRM_CORE_FWD_COPY_CAPTURE(xs)...)))
        {
            return std::make_tuple(VRM_CORE_FWD_COPY_CAPTURE(xs)...);
        }
    }
}

#define VRM_CORE_FWD_CAPTURE_PACK(...) \
    vrm::core::impl::fwd_capture_pack(FWD(__VA_ARGS__)...)

#define VRM_CORE_FWD_COPY_CAPTURE_PACK(...) \
    vrm::core::impl::fwd_copy_capture_pack(FWD(__VA_ARGS__)...)

#if !defined(VRM_CORE_NO_FWD_CAPTURE_PACK_MACRO) && !defined(FWD_CAPTURE_PACK)
#define FWD_CAPTURE_PACK VRM_CORE_FWD_CAPTURE_PACK
#endif

#if !defined(VRM_CORE_NO_FWD_COPY_CAPTURE_PACK_MACRO) && \
    !defined(FWD_COPY_CAPTURE_PACK)
#define FWD_COPY_CAPTURE_PACK VRM_CORE_FWD_COPY_CAPTURE_PACK
#endif
