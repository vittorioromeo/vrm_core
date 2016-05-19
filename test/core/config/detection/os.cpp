#include "../../../utils/test_utils.hpp"
#include <vrm/core/config/detection.hpp>

TEST_MAIN()
{
    using namespace vrm::core;

    auto current_os(detection::current_operating_system());

    TEST_ASSERT(current_os == detection::operating_system::os_linux ||
                current_os == detection::operating_system::os_windows ||
                current_os == detection::operating_system::os_mac ||
                current_os == detection::operating_system::os_freebsd ||
                current_os == detection::operating_system::os_android ||
                current_os == detection::operating_system::os_unknown);

    return 0;
}
