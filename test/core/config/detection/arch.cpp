#include "../../../utils/test_utils.hpp"
#include <vrm/core/config/detection.hpp>

int main()
{
    using namespace vrm::core;

    auto current_arch(detection::current_architecture());

    TEST_ASSERT(current_arch == detection::architecture::x86 ||
                current_arch == detection::architecture::x64);

    return 0;
}