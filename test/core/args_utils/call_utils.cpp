#include "../../utils/test_utils.hpp"
#include <vrm/core/args_utils.hpp>
#include <vrm/core/for_args.hpp>

using namespace vrm::core;

template <typename... Ts>
int TEST_CONST acc(Ts... xs)
{
    int res = 0;
    for_args(
        [&res](auto x)
        {
            res += x;
        },
        xs...);
    return res;
}

TEST_MAIN()
{
    auto a = [](auto... ys)
    {
        return acc(ys...);
    };

    TEST_ASSERT_OP(
        a(1, 2, 3, 4, 5, 6, 7, 8), ==, 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8);

    TEST_ASSERT_OP(call_with_first_n_args<4>(a, 1, 2, 3, 4, 5, 6, 7, 8), // .
        ==, 1 + 2 + 3 + 4);

    TEST_ASSERT_OP(call_with_last_n_args<4>(a, 1, 2, 3, 4, 5, 6, 7, 8), // .
        ==, 5 + 6 + 7 + 8);

    TEST_ASSERT_OP(call_with_all_args_from<4>(a, 1, 2, 3, 4, 5, 6, 7, 8), // .
        ==, 5 + 6 + 7 + 8);

    TEST_ASSERT_OP(call_with_all_args_after<4>(a, 1, 2, 3, 4, 5, 6, 7, 8), // .
        ==, 6 + 7 + 8);

    TEST_ASSERT_OP(call_with_all_args_until<4>(a, 1, 2, 3, 4, 5, 6, 7, 8), // .
        ==, 1 + 2 + 3 + 4 + 5);

    TEST_ASSERT_OP(call_with_all_args_before<4>(a, 1, 2, 3, 4, 5, 6, 7, 8), // .
        ==, 1 + 2 + 3 + 4);
}
