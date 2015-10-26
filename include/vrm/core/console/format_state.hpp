// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cstddef>
#include <cstdint>
#include <vrm/core/config/names.hpp>
#include <vrm/core/console/format_types.hpp>

VRM_CORE_NAMESPACE
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
VRM_CORE_NAMESPACE_END
