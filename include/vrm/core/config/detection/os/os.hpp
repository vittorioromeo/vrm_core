// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/config/detection/os/os_macros.hpp>

VRM_CORE_NAMESPACE
{
    namespace detection
    {
        enum class operating_system
        {
            linux,
            windows,
            mac,
            android,
            freebsd,
            unknown
        };

        constexpr auto current_operating_system() noexcept;

        constexpr auto on_unix() noexcept;
        constexpr auto on_windows() noexcept;
        constexpr auto on_mac() noexcept;
    }
}
VRM_CORE_NAMESPACE_END

#include <vrm/core/config/detection/os/os.inl>