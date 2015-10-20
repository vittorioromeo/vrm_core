// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/internal.hpp>
#include <vrm/core/detection/os/os_macros.hpp>

VRM_CORE_NAMESPACE
{
    namespace detection
    {
        enum class operating_system
        {
            linux,
            windows,
            mac,
            unknown
        };

        constexpr auto current_operating_system() noexcept;
    }
}
VRM_CORE_NAMESPACE_END

#if defined(VRM_CORE_API_HEADERONLY)
#include <vrm/core/detection/os/os.cpp>
#endif