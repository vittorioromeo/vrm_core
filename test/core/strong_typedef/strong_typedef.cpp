#include "../../utils/test_utils.hpp"
#include <vrm/core/strong_typedef.hpp>

VRM_CORE_STRONG_TYPEDEF(int, my_int);
VRM_CORE_STRONG_TYPEDEF(float, my_float);

TEST_MAIN()
{

    my_int x(10);
    my_float f(10.f);

    x = my_int(20);
    f = my_float(20.f);

    return 0;
}

VRM_CORE_STRONG_TYPEDEF_TRAIT(my_int);
VRM_CORE_STRONG_TYPEDEF_TRAIT(my_float);

static_assert(vrm::core::is_strong_typedef_v<my_int>, "");
static_assert(vrm::core::is_strong_typedef_v<my_float>, "");
