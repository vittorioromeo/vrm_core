#include "../../utils/test_utils.hpp"
#include <vrm/core/perfect_wrapper.hpp>

using namespace vrm::core;

TEST_MAIN()
{
    {
        int a = 0;
        perfect_wrapper<int> wa{a};

        ++(wa.get());

        TEST_ASSERT(a == 0);
        TEST_ASSERT(wa == 1);
    }

    {
        int a = 0;
        perfect_wrapper<int&> wa{a};

        ++(wa.get());

        TEST_ASSERT(a == 1);
        TEST_ASSERT(wa == 1);
    }

    {
        int a = 0;
        perfect_wrapper<int&> wa{a};
        auto wa2 = wa;

        ++(wa2.get());

        TEST_ASSERT(a == 1);
        TEST_ASSERT(wa == 1);
        TEST_ASSERT(wa2 == 1);
    }
}
