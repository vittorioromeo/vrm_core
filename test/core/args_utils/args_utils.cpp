#include "../../utils/test_utils.hpp"
#include <vrm/core/args_utils.hpp>

using namespace vrm::core;

struct mv_only
{
    mv_only() = default;

    mv_only(const mv_only&) = delete;
    mv_only& operator=(const mv_only&) = delete;

    mv_only(mv_only&&) = default;
    mv_only& operator=(mv_only&&) = default;
};

void TEST_CONST constexpr_tests()
{
    constexpr auto a0 = nth_arg<0>(1, 2, 3);
    constexpr auto a1 = nth_arg<1>(1, 2, 3);
    constexpr auto a2 = nth_arg<2>(1, 2, 3);

    TEST_ASSERT_OP(a0, ==, 1);
    TEST_ASSERT_OP(a1, ==, 2);
    TEST_ASSERT_OP(a2, ==, 3);

    constexpr auto sub0(args_slice<1, 3>(2, 4, 6, 8, 10));
    auto sr0 = std::get<0>(sub0);
    auto sr1 = std::get<1>(sub0);

    TEST_ASSERT_OP(sr0, ==, 4);
    TEST_ASSERT_OP(sr1, ==, 6);
}


void TEST_CONST non_constexpr_tests()
{
    auto&& a0 = nth_arg<0>(1, 2, 3);
    auto&& a1 = nth_arg<1>(1, 2, 3);
    auto&& a2 = nth_arg<2>(1, 2, 3);

    SA_TYPE((nth_arg<0>(1, 2, 3)), (int));
    SA_TYPE((nth_arg<1>(1, 2, 3)), (int));
    SA_TYPE((nth_arg<2>(1, 2, 3)), (int));

    TEST_ASSERT_OP(a0, ==, 1);
    TEST_ASSERT_OP(a1, ==, 2);
    TEST_ASSERT_OP(a2, ==, 3);



    auto sub0(args_slice<1, 3>(2, 4, 6, 8, 10));
    SA_TYPE((sub0), (std::tuple<int, int>));

    auto sr0 = std::get<0>(sub0);
    auto sr1 = std::get<1>(sub0);

    TEST_ASSERT_OP(sr0, ==, 4);
    TEST_ASSERT_OP(sr1, ==, 6);
}


void TEST_CONST non_constexpr_lv_tests()
{
    auto i0 = 1;
    auto i1 = 2;
    const auto i2 = 3;

    auto& a0 = nth_arg<0>(i0, i1, i2);
    auto& a1 = nth_arg<1>(i0, i1, i2);
    auto& a2 = nth_arg<2>(i0, i1, i2);
    TEST_ASSERT_OP(a0, ==, i0);
    TEST_ASSERT_OP(a1, ==, i1);
    TEST_ASSERT_OP(a2, ==, i2);

    SA_TYPE((nth_arg<0>(i0, i1, i2)), (int&));
    SA_TYPE((nth_arg<1>(i0, i1, i2)), (int&));
    SA_TYPE((nth_arg<2>(i0, i1, i2)), (const int&));

    a0 = 11;
    a1 = 22;
    TEST_ASSERT_OP(a0, ==, 11);
    TEST_ASSERT_OP(a1, ==, 22);
    TEST_ASSERT_OP(a2, ==, i2);

    // Does not compile as intended:
    // a2 = 33;



    auto sub0(args_slice<1, 3>(i0, i1, i2, i0, i1, i2));
    SA_TYPE((sub0), (std::tuple<int&, const int&>));

    auto& sr0 = std::get<0>(sub0);
    auto& sr1 = std::get<1>(sub0);

    TEST_ASSERT_OP(sr0, ==, i1);
    TEST_ASSERT_OP(sr1, ==, i2);

    sr0 = 11;
    TEST_ASSERT_OP(sr0, ==, 11);
    TEST_ASSERT_OP(sr1, ==, i2);


    // Does not compile as intended:
    // sr1 = 22;
}

void TEST_CONST move_only_tests()
{
    auto&& a0 = nth_arg<0>(mv_only{}, 2, 3);
    auto&& a1 = nth_arg<1>(mv_only{}, 2, 3);
    auto&& a2 = nth_arg<2>(mv_only{}, 2, 3);

    SA_TYPE((nth_arg<0>(mv_only{}, 2, 3)), (mv_only));
    SA_TYPE((nth_arg<1>(mv_only{}, 2, 3)), (int));
    SA_TYPE((nth_arg<2>(mv_only{}, 2, 3)), (int));

    auto r0(std::move(a0));
    auto r1 = a1;
    auto r2 = a2;

    (void)r0;
    TEST_ASSERT_OP(r1, ==, 2);
    TEST_ASSERT_OP(r2, ==, 3);

    auto sub0(args_slice<1, 3>(2, mv_only{}, 6, 8, 10));
    SA_TYPE((sub0), (std::tuple<mv_only, int>));

    auto sr0(std::move(std::get<0>(sub0)));
    auto sr1 = std::get<1>(sub0);

    (void)sr0;
    TEST_ASSERT_OP(sr1, ==, 6);
}

TEST_MAIN()
{
    constexpr_tests();
    non_constexpr_tests();
    non_constexpr_lv_tests();
    move_only_tests();
}
