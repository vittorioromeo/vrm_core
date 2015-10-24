// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <vrm/core/detection/os/os.hpp>

VRM_CORE_NAMESPACE
{
    namespace detection
    {
        VRM_CORE_API constexpr auto current_operating_system() noexcept
        {
#if defined(VRM_CORE_OS_LINUX)
            return operating_system::linux;
#elif defined(VRM_CORE_OS_ANDROID)
            return operating_system::android;
#elif defined(VRM_CORE_OS_FREEBSD)
            return operating_system::freebsd;
#elif defined(VRM_CORE_OS_WINDOWS)
            return operating_system::windows;
#elif defined(VRM_CORE_OS_MAC)
            return operating_system::mac;
#else
            return operating_system::unknown;
#endif
        }

        constexpr auto on_unix() noexcept
        {
            return current_operating_system() == operating_system::linux ||
                   current_operating_system() == operating_system::android ||
                   current_operating_system() == operating_system::freebsd;
        }

        constexpr auto on_windows() noexcept
        {
            return current_operating_system() == operating_system::windows;
        }

        constexpr auto on_mac() noexcept
        {
            return current_operating_system() == operating_system::mac;
        }
    }
}
VRM_CORE_NAMESPACE_END