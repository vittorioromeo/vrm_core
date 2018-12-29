// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/utility_macros.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <typename... TFs>
        struct overload_set : TFs...
        {
            constexpr VRM_CORE_ALWAYS_INLINE overload_set(TFs&&... fs) noexcept(
                (noexcept(TFs(FWD(fs))) && ...))
                : TFs(FWD(fs))...
            {
            }

            using TFs::operator()...;
        };
    } // namespace impl

    template <typename... TFs>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto make_overload(
        TFs&&... fs) noexcept(noexcept(impl::overload_set<TFs...>{FWD(fs)...}))
    {
        return impl::overload_set<TFs...>{FWD(fs)...};
    }
} // namespace vrm::core
