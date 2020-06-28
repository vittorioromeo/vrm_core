#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/self.hpp>

TEST_MAIN()
{
    using namespace vrm::core;

    int i(0);
    (void)self_cast<int>(i);
    (void)self_cast<const int>(i);

    // Does not compile as intended:
    // (void) self_cast<int*>(i);

    // Does not compile as intended:
    // (void) self_cast<int**>(i);

    (void)self_cast<int&>(i);
    (void)self_cast<int&&>(i);
    (void)self_cast<const int&>(i);
    (void)self_cast<const int&&>(i);
    (void)((int)self_cast<volatile int&>(i));
    (void)((int)self_cast<volatile int&&>(i));

    return 0;
}
