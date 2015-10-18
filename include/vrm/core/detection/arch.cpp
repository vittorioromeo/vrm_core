// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <vrm/core/detection/arch.hpp>

VRM_CORE_NAMESPACE
{
    namespace detection
    {
        VRM_CORE_API_INLINE constexpr auto current_architecture() noexcept
        {
#if defined(VRM_CORE_ARCH_32)
            return architecture::x86;
#elif defined(VRM_CORE_ARCH_64)
            return architecture::x64;
#else
            return architecture::unknown;
#endif
        }
    }
}
VRM_CORE_NAMESPACE_END