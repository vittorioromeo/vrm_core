#include "../../utils/test_utils.hpp"
#include <vrm/core/detection.hpp>

int main()
{
    using namespace vrm::core;

    auto current_debug(detection::debug());

    TEST_ASSERT(current_debug == true || current_debug == false);

    return 0;
}