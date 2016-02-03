#include "../../utils/test_utils.hpp"

#define VRM_CORE_ASSERT_FORCE_ON 1
#include <vrm/core/assert.hpp>

template<int TI> struct s
{
    int x() { return TI; }
};

template<int TI>
constexpr int test_cexpr()
{
    VRM_CORE_CONSTEXPR_ASSERT(TI > 5);
    return TI + 1;
}

TEST_MAIN()
{
    s<test_cexpr<10>()> y{};
    TEST_ASSERT_OP((y.x()), ==, 11);
    return 0;
}
