#include "../../utils/test_utils.hpp"

#define VRM_CORE_ASSERT_FORCE_OFF 1
#include <vrm/core/assert.hpp>

constexpr int test_cexpr()
{
    constexpr auto lhs = 10;
    constexpr auto rhs = 15;

    VRM_CORE_CONSTEXPR_ASSERT_OP_MSG(lhs + 6, >, rhs, "test message");
    VRM_CORE_CONSTEXPR_ASSERT_OP(lhs + 7, >, rhs);
    VRM_CORE_CONSTEXPR_ASSERT_MSG(lhs + 8 > rhs, "test message");
    VRM_CORE_CONSTEXPR_ASSERT(lhs + 9 > rhs);

    (void)lhs;
    (void)rhs;

    return 0;
}

TEST_MAIN()
{
    VRM_CORE_STATIC_ASSERT(true, "");
    VRM_CORE_STATIC_ASSERT_NM(true);

    using namespace vrm::core;

    auto lhs = 10;
    auto rhs = 15;

    VRM_CORE_ASSERT_OP_MSG(lhs + 6, >, rhs, "test message");
    VRM_CORE_ASSERT_OP(lhs + 7, >, rhs);
    VRM_CORE_ASSERT_MSG((lhs + 8) > rhs, "test message");
    VRM_CORE_ASSERT((lhs + 9) > rhs);

    volatile int x = test_cexpr();
    constexpr int y = test_cexpr();

    (void)lhs;
    (void)rhs;
    (void)x;
    (void)y;

    return 0;
}
