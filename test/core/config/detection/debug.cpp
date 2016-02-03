#include "../../../utils/test_utils.hpp"
#include <vrm/core/config/detection.hpp>

TEST_MAIN()
{
    using namespace vrm::core;

    auto current_debug(detection::debug());

    TEST_ASSERT(current_debug == true || current_debug == false);

    return 0;
}
