// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

namespace vrm::core::detection
{
    enum class compiler
    {
        clang,
        gcc,
        mscv,
        unknown
    };

    constexpr auto current_compiler() noexcept;
} // namespace vrm::core::detection
