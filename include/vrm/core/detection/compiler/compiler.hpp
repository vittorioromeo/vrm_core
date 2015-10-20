// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/internal.hpp>
#include <vrm/core/detection/compiler/compiler_macros.hpp>

VRM_CORE_NAMESPACE
{
    namespace detection
    {
        enum class compiler
        {
            clang,
            gcc,
            unknown
        };

        constexpr auto current_compiler() noexcept;
    }
}
VRM_CORE_NAMESPACE_END

#if defined(VRM_CORE_API_HEADERONLY)
#include <vrm/core/detection/compiler.cpp>
#endif