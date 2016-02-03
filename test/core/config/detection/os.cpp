#include "../../../utils/test_utils.hpp"
#include <vrm/core/config/detection.hpp>

TEST_MAIN()
{
    using namespace vrm::core;

    auto current_os(detection::current_operating_system());

    TEST_ASSERT(current_os == detection::operating_system::linux ||
                current_os == detection::operating_system::windows ||
                current_os == detection::operating_system::mac);

    return 0;
}
