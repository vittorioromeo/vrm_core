// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/detection/os/impl/os.hpp>
#include <vrm/core/config/detection/os/impl/os_macros.hpp>

namespace vrm::core::detection
{
    [[nodiscard]] inline constexpr operating_system
    current_operating_system() noexcept
    {
#if defined(VRM_CORE_OS_LINUX)
        return operating_system::os_linux;
#elif defined(VRM_CORE_OS_ANDROID)
        return operating_system::os_android;
#elif defined(VRM_CORE_OS_FREEBSD)
        return operating_system::os_freebsd;
#elif defined(VRM_CORE_OS_WINDOWS)
        return operating_system::os_windows;
#elif defined(VRM_CORE_OS_MAC)
        return operating_system::os_mac;
#else
        return operating_system::os_unknown;
#endif
    }

    [[nodiscard]] inline constexpr bool on_unix() noexcept
    {
        return current_operating_system() == operating_system::os_linux ||
               current_operating_system() == operating_system::os_android ||
               current_operating_system() == operating_system::os_freebsd;
    }

    [[nodiscard]] inline constexpr bool on_windows() noexcept
    {
        return current_operating_system() == operating_system::os_windows;
    }

    [[nodiscard]] inline constexpr bool on_mac() noexcept
    {
        return current_operating_system() == operating_system::os_mac;
    }
} // namespace vrm::core::detection
