#include "../../utils/test_utils.hpp"
#include <vrm/core/strong_typedef.hpp>

TEST_MAIN()
{
    VRM_CORE_STRONG_TYPEDEF(int, my_int);
    VRM_CORE_STRONG_TYPEDEF(float, my_float);

    my_int x(10);
    my_float f(10.f);

    x = my_int(20);
    f = my_float(20.f);

    return 0;
}
