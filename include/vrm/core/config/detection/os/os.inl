// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <vrm/core/config/detection/os/os_macros.hpp>
#include <vrm/core/config/detection/os/os.hpp>

VRM_CORE_NAMESPACE
{
    namespace detection
    {
        inline constexpr auto current_operating_system() noexcept
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

        inline constexpr auto on_unix() noexcept
        {
            return current_operating_system() == operating_system::linux ||
                   current_operating_system() == operating_system::android ||
                   current_operating_system() == operating_system::freebsd;
        }

        inline constexpr auto on_windows() noexcept
        {
            return current_operating_system() == operating_system::windows;
        }

        inline constexpr auto on_mac() noexcept
        {
            return current_operating_system() == operating_system::mac;
        }
    }
}
VRM_CORE_NAMESPACE_END