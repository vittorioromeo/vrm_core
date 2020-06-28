// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

namespace vrm::core::detection
{
    enum class operating_system
    {
        os_linux,
        os_windows,
        os_mac,
        os_android,
        os_freebsd,
        os_unknown
    };

    [[nodiscard]] constexpr operating_system
    current_operating_system() noexcept;

    [[nodiscard]] constexpr bool on_unix() noexcept;
    [[nodiscard]] constexpr bool on_windows() noexcept;
    [[nodiscard]] constexpr bool on_mac() noexcept;
} // namespace vrm::core::detection
