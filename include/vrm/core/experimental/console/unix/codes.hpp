// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cstddef>
#include <cstdint>
#include <vrm/core/config/names.hpp>
#include <vrm/core/make_array.hpp>
#include <vrm/core/experimental/console/format_types.hpp>
#include <vrm/core/experimental/console/format_state.hpp>

VRM_CORE_NAMESPACE
{
    namespace console
    {
        namespace impl
        {
            constexpr const char* code_prefix{"\033["};
            constexpr const char* code_postfix{"m"};
            constexpr const char* code_clear{"\033[1;1H\033[2J"};

            VRM_CORE_ALWAYS_INLINE const auto& style_code_ids() noexcept
            {
                static auto ids(make_array(0, // 0 = style::none
                    1,                        // 1 = style::bold
                    2,                        // 2 = style::dim
                    4,                        // 3 = style::underline
                    5,                        // 4 = style::blink
                    7,                        // 5 = style::reverse_fg_bg
                    8,                        // 6 = style::hidden
                    21,                       // 7 = (?) style::ResetBold
                    22,                       // 8 = (?) style::ResetDim
                    24,                       // 9 = (?) style::ResetUnderline
                    25,                       // 10 = (?) style::ResetBlink
                    27,                       // 11 = (?) style::ResetReverse
                    28                        // 12 = (?) style::ResetHidden
                    ));

                return ids;
            }

            VRM_CORE_ALWAYS_INLINE const auto& color_fg_code_ids() noexcept
            {
                static auto ids(make_array(39, // 0 = color::none
                    30,                        // 1 = color::black
                    31,                        // 2 = color::red
                    32,                        // 3 = color::green
                    33,                        // 4 = color::yellow
                    34,                        // 5 = color::blue
                    35,                        // 6 = color::magenta
                    36,                        // 7 = color::cyan
                    37,                        // 8 = color::light_gray
                    90,                        // 9 = color::dark_gray
                    91,                        // 10 = color::light_red
                    92,                        // 11 = color::light_green
                    93,                        // 12 = color::light_yellow
                    94,                        // 13 = color::light_blue
                    95,                        // 14 = color::light_magenta
                    96,                        // 15 = color::light_cyan
                    97                         // 16 = color::light_white
                    ));

                return ids;
            }

            VRM_CORE_ALWAYS_INLINE const auto& color_bg_code_ids() noexcept
            {
                static auto ids(make_array(49, // 0 = color::none
                    40,                        // 1 = color::black
                    41,                        // 2 = color::red
                    42,                        // 3 = color::green
                    43,                        // 4 = color::yellow
                    44,                        // 5 = color::blue
                    45,                        // 6 = color::magenta
                    46,                        // 7 = color::cyan
                    47,                        // 8 = color::light_gray
                    100,                       // 9 = color::dark_gray
                    101,                       // 10 = color::light_red
                    102,                       // 11 = color::light_green
                    103,                       // 12 = color::light_yellow
                    104,                       // 13 = color::light_blue
                    105,                       // 14 = color::light_magenta
                    106,                       // 15 = color::light_cyan
                    107                        // 16 = color::light_white
                    ));

                return ids;
            }

            // VRM_CORE_ALWAYS_INLINE const auto& style_codes() noexcept
            // {}
        }
    }
}
VRM_CORE_NAMESPACE_END
