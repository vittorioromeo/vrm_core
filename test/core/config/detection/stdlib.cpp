#include "../../../utils/test_utils.hpp"
#include <vrm/core/config/detection.hpp>

TEST_MAIN()
{
    using namespace vrm::core;

    auto current_stdlib(detection::current_stdlib());

    TEST_ASSERT(current_stdlib == detection::stdlib::libcxx ||
                current_stdlib == detection::stdlib::libstdcxx);

    return 0;
}
