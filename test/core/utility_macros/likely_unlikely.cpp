#include "../../utils/test_utils.hpp"
#include <vrm/core/utility_macros.hpp>

int main()
{
    using namespace vrm::core;

    volatile int x = 10;
    volatile bool y = true;

    if(likely(x))
    {
        TEST_ASSERT(true);
    }

    if(unlikely(y))
    {
        TEST_ASSERT(true);
    }

    return 0;
}
