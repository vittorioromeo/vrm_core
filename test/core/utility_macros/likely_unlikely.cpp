#include "../../utils/test_utils.hpp"
#include <vrm/core/utility_macros.hpp>

int main()
{
    using namespace vrm::core;

    volatile int x = 10;
    volatile bool y = true;

    if(VRM_CORE_LIKELY(x))
    {
        TEST_ASSERT(true);
    }

    if(VRM_CORE_UNLIKELY(y))
    {
        TEST_ASSERT(true);
    }

    return 0;
}