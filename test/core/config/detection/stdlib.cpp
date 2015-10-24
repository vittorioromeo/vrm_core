#include "../../../utils/test_utils.hpp"
#include <vrm/core/config/detection.hpp>

int main()
{
    using namespace vrm::core;

    auto current_stdlib(detection::current_stdlib());

    TEST_ASSERT(current_stdlib == detection::stdlib::libcxx ||
                current_stdlib == detection::stdlib::libstdcxx);

    return 0;
}