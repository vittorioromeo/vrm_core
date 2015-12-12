#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/self.hpp>

int main()
{
    using namespace vrm::core;

    int i;
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
    (void)((volatile int)self_cast<volatile int&>(i));
    (void)((volatile int)self_cast<volatile int&&>(i));

    return 0;
}
