#include "../../utils/test_utils.hpp"
#include <vrm/core/config.hpp>
#include <typeinfo>
#include <vrm/core/for_args.hpp>
#include <vrm/core/tuple_utils/transpose.hpp>

using namespace vrm::core;

void test0()
{
    auto t = std::make_tuple(0, 'a', 1, 'b');
    auto t_r = make_ref_tuple(0, 'a', 1, 'b');
    auto t_f = std::forward_as_tuple(0, 'a', 1, 'b');

    auto tt = to_transposed_tuple<2>(t);
    auto tt_r = to_transposed_ref_tuple<2>(t);
    auto tt_f = to_forwarded_transposed_tuple<2>(t);

    SA_TYPE((std::get<0>(t)), (int&));
    SA_TYPE((std::get<0>(t_r)), (int&));
    SA_TYPE((std::get<0>(t_f)), (int&));

    SA_TYPE((std::get<0>(tt)), (int&));
    SA_TYPE((std::get<0>(tt_r)), (int&));
    SA_TYPE((std::get<0>(tt_f)), (int&));

    for_args(
        [&](auto&& y)
        {
            TEST_ASSERT_OP(std::get<0>(t), ==, std::get<0>(y));
            TEST_ASSERT_OP(std::get<1>(t), ==, std::get<1>(y));
            TEST_ASSERT_OP(std::get<2>(t), ==, std::get<2>(y));
            TEST_ASSERT_OP(std::get<3>(t), ==, std::get<3>(y));
        },
        t, t_r, t_f);

    for_args(
        [&](auto&& x)
        {
            TEST_ASSERT_OP(std::get<0>(t), ==, std::get<0>(x));
            TEST_ASSERT_OP(std::get<1>(t), ==, std::get<2>(x));
            TEST_ASSERT_OP(std::get<2>(t), ==, std::get<1>(x));
            TEST_ASSERT_OP(std::get<3>(t), ==, std::get<3>(x));
        },
        tt, tt_r, tt_f);

    TEST_ASSERT_OP(std::get<0>(t), ==, 0);
    TEST_ASSERT_OP(std::get<2>(t), ==, 1);
    TEST_ASSERT_OP(std::get<1>(t), ==, 'a');
    TEST_ASSERT_OP(std::get<3>(t), ==, 'b');
    TEST_ASSERT_OP(std::get<0>(tt_f), ==, 0);
    TEST_ASSERT_OP(std::get<1>(tt_f), ==, 1);
    TEST_ASSERT_OP(std::get<2>(tt_f), ==, 'a');
    TEST_ASSERT_OP(std::get<3>(tt_f), ==, 'b');
}

void test1()
{
    auto t = std::make_tuple(0, 'a', 1, 'b', 2, 'c');
    auto tt = to_transposed_tuple<3>(t);
    auto tt_r = to_transposed_ref_tuple<3>(t);
    auto tt_f = to_forwarded_transposed_tuple<3>(t);

    for_args(
        [&](auto&& x)
        {
            TEST_ASSERT_OP(std::get<0>(t), ==, std::get<0>(x));
            TEST_ASSERT_OP(std::get<1>(t), ==, std::get<3>(x));
            TEST_ASSERT_OP(std::get<2>(t), ==, std::get<1>(x));
            TEST_ASSERT_OP(std::get<3>(t), ==, std::get<4>(x));
            TEST_ASSERT_OP(std::get<4>(t), ==, std::get<2>(x));
            TEST_ASSERT_OP(std::get<5>(t), ==, std::get<5>(x));
        },
        tt, tt_r, tt_f);
}

void test2()
{
    auto t = std::make_tuple(0, 'a', 1, 'b');
    auto t_r = make_ref_tuple(0, 'a', 1, 'b');
    auto t_f = std::forward_as_tuple(0, 'a', 1, 'b');

    auto ttn = make_transposed_tuple<2>(0, 'a', 1, 'b');
    auto ttn_r = make_transposed_ref_tuple<2>(0, 'a', 1, 'b');
    auto ttn_f = forward_as_transposed_tuple<2>(0, 'a', 1, 'b');

    auto tt = to_transposed_tuple<2>(t);
    auto tt_r = to_transposed_ref_tuple<2>(t_r);
    auto tt_f = to_forwarded_transposed_tuple<2>(t_f);

    SA_TYPE((t), (std::tuple<int, char, int, char>));
    SA_TYPE((t_r), (std::tuple<int, char, int, char>));
    SA_TYPE((t_f), (std::tuple<int&&, char&&, int&&, char&&>));

    SA_TYPE((ttn), (std::tuple<int, int, char, char>));
    SA_TYPE((ttn_r), (std::tuple<int, int, char, char>));
    SA_TYPE((ttn_f), (std::tuple<int&&, int&&, char&&, char&&>));

    SA_TYPE((tt), (std::tuple<int, int, char, char>));
    SA_TYPE((tt_r), (std::tuple<int&, int&, char&, char&>));
    SA_TYPE((tt_f), (std::tuple<int&, int&, char&, char&>));

    SA_TYPE((std::get<0>(t)), (int&));
    SA_TYPE((std::get<0>(std::move(t))), (int&&));

    SA_TYPE((std::get<0>(t_r)), (int&));
    SA_TYPE((std::get<0>(std::move(t_r))), (int&&));

    SA_TYPE((std::get<0>(t_f)), (int&));
    SA_TYPE((std::get<0>(std::move(t_f))), (int&&));



    SA_TYPE((std::get<0>(tt)), (int&));
    SA_TYPE((std::get<0>(std::move(tt))), (int&&));

    SA_TYPE((std::get<0>(tt_r)), (int&));
    SA_TYPE((std::get<0>(std::move(tt_r))), (int&));

    SA_TYPE((std::get<0>(tt_f)), (int&));
    SA_TYPE((std::get<0>(std::move(tt_f))), (int&));



    SA_TYPE((std::get<0>(ttn)), (int&));
    SA_TYPE((std::get<0>(std::move(ttn))), (int&&));

    SA_TYPE((std::get<0>(ttn_r)), (int&));
    SA_TYPE((std::get<0>(std::move(ttn_r))), (int&&));

    SA_TYPE((std::get<0>(ttn_f)), (int&));
    SA_TYPE((std::get<0>(std::move(ttn_f))), (int&&));
}
/*
void test3()
{
    int i = 1;
    int i2 = 3;
    auto t = std::tuple<int, int&, int&&, int*>(0, i, 2, &i2);
    auto tt = to_transposed_tuple<2>(t);
    auto tt_r = to_transposed_ref_tuple<2>(t);
    auto tt_f = to_forwarded_transposed_tuple<2>(t);

    SA_TYPE((std::get<0>(tt)), (int&));
    SA_TYPE((std::get<1>(tt)), (int&));
    SA_TYPE((std::get<2>(tt)), (int&));
    SA_TYPE((std::get<3>(tt)), (int*&));
    SA_TYPE((std::get<0>(std::move(tt))), (int&&));
    SA_TYPE((std::get<1>(std::move(tt))), (int&&));
    SA_TYPE((std::get<2>(std::move(tt))), (int&&));
    SA_TYPE((std::get<3>(std::move(tt))), (int*&&));

    SA_TYPE((std::get<0>(tt_r)), (int&));
    SA_TYPE((std::get<1>(tt_r)), (int&));
    SA_TYPE((std::get<2>(tt_r)), (int&));
    SA_TYPE((std::get<3>(tt_r)), (int*&));
    SA_TYPE((std::get<0>(std::move(tt_r))), (int&));
    SA_TYPE((std::get<1>(std::move(tt_r))), (int&));
    SA_TYPE((std::get<2>(std::move(tt_r))), (int&));
    SA_TYPE((std::get<3>(std::move(tt_r))), (int*&));

    SA_TYPE((std::get<0>(tt_f)), (int&));
    SA_TYPE((std::get<1>(tt_f)), (int&));
    SA_TYPE((std::get<2>(tt_f)), (int&));
    SA_TYPE((std::get<3>(tt_f)), (int*&));
    SA_TYPE((std::get<0>(std::move(tt_f))), (int&));
    SA_TYPE((std::get<1>(std::move(tt_f))), (int&));
    SA_TYPE((std::get<2>(std::move(tt_f))), (int&));
    SA_TYPE((std::get<3>(std::move(tt_f))), (int*&));
}
*/

int main()
{
    test0();
    test1();
    test2();
    // test3();

    return 0;
}

// TODO:
