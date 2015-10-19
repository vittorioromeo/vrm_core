#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/arithmetic.hpp>

int main()
{
    using namespace vrm::core;

    int i = 1;

    TEST_ASSERT(i == 1);
    TEST_ASSERT(to_int(i) == 1);
    TEST_ASSERT(to_float(i) == 1.f);
    TEST_ASSERT(to_double(i) == 1);
    TEST_ASSERT(to_size_t(i) == 1);
    TEST_ASSERT(to_num<long>(i) == 1.f);

    // Will fire assertion:
    // TEST_ASSERT(to_size_t<int>(int(-1)) == -1);

    return 0;
}