// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

namespace vrm::core::detection
{
    enum class stdlib
    {
        libcxx,
        libstdcxx,
        unknown
    };

    constexpr auto current_stdlib() noexcept;
} // namespace vrm::core::detection
