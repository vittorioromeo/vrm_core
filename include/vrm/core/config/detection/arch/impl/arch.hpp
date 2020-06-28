// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

namespace vrm::core::detection
{
    enum class architecture
    {
        x86,
        x64,
        unknown
    };

    [[nodiscard]] constexpr architecture current_architecture() noexcept;
} // namespace vrm::core::detection
