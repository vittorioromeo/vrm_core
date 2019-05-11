#include "../../utils/test_utils.hpp"
#include <vrm/core/value_wrapper.hpp>

using namespace vrm::core;

TEST_MAIN()
{
    {
        int a = 0;
        value_wrapper<int> wa{a};

        ++(wa.get());

        TEST_ASSERT(a == 0);
        TEST_ASSERT(wa == 1);
    }

    {
        auto l = [](int) { return 2; };
        value_wrapper<decltype(l)> w(std::move(l));
        (void)w;
        TEST_ASSERT(l(42) == 2);
    }
}
