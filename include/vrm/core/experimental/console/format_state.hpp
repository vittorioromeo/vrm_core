// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cstddef>
#include <cstdint>
#include <vrm/core/experimental/console/format_types.hpp>

namespace vrm::core
{
    namespace console
    {
        namespace impl
        {
            struct format_state
            {
                style _style{style::none};
                color _fg_color{color::none};
                color _bg_color{color::none};
            };
        }
    }
}
