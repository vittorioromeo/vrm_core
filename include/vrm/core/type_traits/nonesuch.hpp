// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

namespace vrm::core
{
    struct nonesuch
    {
        nonesuch() = delete;
        ~nonesuch() = delete;

        nonesuch(const nonesuch&) = delete;
        nonesuch(nonesuch&&) = delete;

        nonesuch& operator=(const nonesuch&) = delete;
        nonesuch& operator=(nonesuch&&) = delete;
    };
} // namespace vrm::core
