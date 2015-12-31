// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cstddef>
#include <cstdint>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

VRM_CORE_NAMESPACE
{
    namespace console
    {
        namespace impl
        {
            using style_type = i8;
            using color_type = i8;

            /// @brief Number of styles.
            constexpr sz_t style_count{13};

            /// @brief Number of colors.
            constexpr sz_t color_count{16};
        }

        /// @brief Enum class representing all the possible styles.
        enum class style : impl::style_type
        {
            none = 0,
            bold = 1,
            dim = 2,
            underline = 3,
            blink = 4,
            reverse_fg_bg = 5,
            hidden = 6
        };

        /// @brief Enum class representing all the possible colors.
        enum class color : impl::color_type
        {
            none = 0,
            black = 1,
            red = 2,
            green = 3,
            yellow = 4,
            blue = 5,
            magenta = 6,
            cyan = 7,
            light_gray = 8,
            dark_gray = 9,
            light_red = 10,
            light_green = 11,
            light_yellow = 12,
            light_blue = 13,
            light_magenta = 14,
            light_cyan = 15,
            light_white = 16
        };
    }
}
VRM_CORE_NAMESPACE_END
