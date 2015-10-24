// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <vrm/core/config/detection/compiler/compiler_macros.hpp>
#include <vrm/core/config/detection/compiler/compiler.hpp>

VRM_CORE_NAMESPACE
{
    namespace detection
    {
        inline constexpr auto current_compiler() noexcept
        {
#if defined(VRM_CORE_COMPILER_CLANG)
            return compiler::clang;
#elif defined(VRM_CORE_COMPILER_GCC)
            return compiler::gcc;
#elif defined(VRM_CORE_COMPILER_MSCV)
            return compiler::mscv;
#else
            return compiler::unknown;
#endif
        }
    }
}
VRM_CORE_NAMESPACE_END