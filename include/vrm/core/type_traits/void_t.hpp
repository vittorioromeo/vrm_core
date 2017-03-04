// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Variadic template alias that always evaluates to `void`.
    template <typename...>
    using void_t = void;
}
VRM_CORE_NAMESPACE_END
