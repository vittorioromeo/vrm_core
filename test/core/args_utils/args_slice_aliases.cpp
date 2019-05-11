#include "../../utils/test_utils.hpp"
#include <vrm/core/args_utils.hpp>

using namespace vrm::core;

void t0()
{
    {
        auto s0 = first_n_args<3>(0, 1, 2, 3, 4, 5, 6);
        static_assert(std::tuple_size<decltype(s0)>{} == 3, "");
        TEST_ASSERT_OP(std::get<0>(s0), ==, 0);
        TEST_ASSERT_OP(std::get<1>(s0), ==, 1);
        TEST_ASSERT_OP(std::get<2>(s0), ==, 2);
    }
    {
        auto s1 = last_n_args<3>(0, 1, 2, 3, 4, 5, 6);
        static_assert(std::tuple_size<decltype(s1)>{} == 3, "");
        TEST_ASSERT_OP(std::get<0>(s1), ==, 4);
        TEST_ASSERT_OP(std::get<1>(s1), ==, 5);
        TEST_ASSERT_OP(std::get<2>(s1), ==, 6);
    }
    {
        auto s2 = first_n_args<1>(0, 1, 2, 3, 4, 5, 6);
        static_assert(std::tuple_size<decltype(s2)>{} == 1, "");
        TEST_ASSERT_OP(std::get<0>(s2), ==, 0);
    }
    {
        auto s3 = last_n_args<1>(0, 1, 2, 3, 4, 5, 6);
        static_assert(std::tuple_size<decltype(s3)>{} == 1, "");
        TEST_ASSERT_OP(std::get<0>(s3), ==, 6);
    }
    {
        auto s4 = first_n_args<0>(0, 1, 2, 3, 4, 5, 6);
        static_assert(std::tuple_size<decltype(s4)>{} == 0, "");
    }
    {
        auto s5 = last_n_args<0>(0, 1, 2, 3, 4, 5, 6);
        static_assert(std::tuple_size<decltype(s5)>{} == 0, "");
    }

    {
        auto x = first_arg(0, 1, 2, 3, 4, 5, 6);
        SA_TYPE((x), (int));
        TEST_ASSERT_OP(x, ==, 0);
    }

    {
        auto x = last_arg(0, 1, 2, 3, 4, 5, 6);
        SA_TYPE((x), (int));
        TEST_ASSERT_OP(x, ==, 6);
    }
}

void empty()
{
    {
        auto s0 = first_n_args<0>();
        static_assert(std::tuple_size<decltype(s0)>{} == 0, "");
    }

    {
        auto s0 = last_n_args<0>();
        static_assert(std::tuple_size<decltype(s0)>{} == 0, "");
    }

    {
        auto s0 = all_args_from<0>();
        static_assert(std::tuple_size<decltype(s0)>{} == 0, "");
    }

    {
        auto s0 = all_args_before<0>();
        static_assert(std::tuple_size<decltype(s0)>{} == 0, "");
    }
}

void t1(){
#define MT ::std::make_tuple

    {auto s = first_n_args<3>(0, 1, 2, 3, 4, 5, 6);
TEST_ASSERT(MT(0, 1, 2) == s);
}
{
    auto s = last_n_args<3>(0, 1, 2, 3, 4, 5, 6);
    TEST_ASSERT(MT(4, 5, 6) == s);
}
{
    auto s = all_args_from<3>(0, 1, 2, 3, 4, 5, 6);
    TEST_ASSERT(MT(3, 4, 5, 6) == s);
}
{
    auto s = all_args_after<3>(0, 1, 2, 3, 4, 5, 6);
    TEST_ASSERT(MT(4, 5, 6) == s);
}
{
    auto s = all_args_until<3>(0, 1, 2, 3, 4, 5, 6);
    TEST_ASSERT(MT(0, 1, 2, 3) == s);
}
{
    auto s = all_args_before<3>(0, 1, 2, 3, 4, 5, 6);
    TEST_ASSERT(MT(0, 1, 2) == s);
}
{
    auto s = first_arg(0, 1, 2, 3, 4, 5, 6);
    TEST_ASSERT(0 == s);
}
{
    auto s = last_arg(0, 1, 2, 3, 4, 5, 6);
    TEST_ASSERT(6 == s);
}

#undef MT
}

TEST_MAIN()
{
    t0();
    empty();
    t1();
    return 0;
}
