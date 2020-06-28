// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/utility_macros.hpp>

namespace vrm::core
{
    template <typename... TFs>
    struct overload_set : TFs...
    {
        explicit constexpr VRM_CORE_ALWAYS_INLINE overload_set(
            TFs&&... fs) noexcept((noexcept(TFs(FWD(fs))) && ...))
            : TFs(FWD(fs))...
        {
        }

        using TFs::operator()...;
    };
} // namespace vrm::core
