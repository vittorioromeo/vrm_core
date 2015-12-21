#include "../../../utils/test_utils.hpp"
#include <vrm/core/experimental/delegate.hpp>

using namespace vrm::core;

void prev_tests()
{
    bool testState{false};
    dynamic_delegate<void()> del1;
    del1 += [&testState]
    {
        testState = !testState;
    };

    del1();
    TEST_ASSERT(testState == true);
    del1();
    TEST_ASSERT(testState == false);

    dynamic_delegate<int(int)> del2;
    del2 += [](int x)
    {
        return x + x;
    };
    del2 += [](int x)
    {
        return x * x;
    };

    std::vector<int> del2result;

    del2.call_and_use_result(
        [&](auto x)
        {
            del2result.emplace_back(x);
        },
        3);
    TEST_ASSERT(del2result[0] == 6);
    TEST_ASSERT(del2result[1] == 9);
    TEST_ASSERT(del2result.size() == 2);

    dynamic_delegate<void()> del3;
    del3 += [&del1]
    {
        del1();
    };
    del3();
    TEST_ASSERT(testState == true);

    dynamic_delegate<void(int&)> del4;
    del4 += [](int& i)
    {
        i += 1;
    };
    del4 += [](int& i)
    {
        i += 1;
    };

    int f = 0;
    del4(f);
    TEST_ASSERT_OP(f, ==, 2);
    del4(f);
    TEST_ASSERT_OP(f, ==, 4);
    del4(f);
    TEST_ASSERT_OP(f, ==, 6);
    del4(f);
    TEST_ASSERT_OP(f, ==, 8);

    {
        int i = 0;
        dynamic_delegate<int()> del5;
        del5 += [i]() mutable
        {
            i += 1;
            return i;
        };
        TEST_ASSERT_OP(del5.call_and_return_vector()[0], ==, 1);
        TEST_ASSERT_OP(del5.call_and_return_vector()[0], ==, 2);
        TEST_ASSERT_OP(del5.call_and_return_vector()[0], ==, 3);
        TEST_ASSERT_OP(del5.call_and_return_vector()[0], ==, 4);
        TEST_ASSERT_OP(del5.call_and_return_vector()[0], ==, 5);
        TEST_ASSERT_OP(del5.call_and_return_vector()[0], ==, 6);
        TEST_ASSERT_OP(del5.call_and_return_vector()[0], ==, 7);
    }
}

int main()
{
    prev_tests();

    dynamic_delegate<int(int)> d;
    auto h_doubler = d += [](int x)
    {
        return x * 2;
    };
    auto h_adder = d += [](int x)
    {
        return x + 1;
    };

    auto fold_res([&d](auto x)
        {
            auto v = d.call_and_return_vector(x);
            int acc = 0;
            for(auto dv : v) acc += dv;
            return acc;
        });

    TEST_ASSERT_OP(fold_res(0), ==, 1);
    TEST_ASSERT_OP(fold_res(1), ==, 4);
    TEST_ASSERT_OP(fold_res(2), ==, 7);
    TEST_ASSERT_OP(fold_res(3), ==, 10);

    d -= h_adder;

    TEST_ASSERT_OP(fold_res(0), ==, 0);
    TEST_ASSERT_OP(fold_res(1), ==, 2);
    TEST_ASSERT_OP(fold_res(2), ==, 4);
    TEST_ASSERT_OP(fold_res(3), ==, 6);

    d -= h_doubler;

    TEST_ASSERT_OP(fold_res(0), ==, 0);
    TEST_ASSERT_OP(fold_res(1), ==, 0);
    TEST_ASSERT_OP(fold_res(2), ==, 0);
    TEST_ASSERT_OP(fold_res(3), ==, 0);

    auto h_triple = d += [](int x)
    {
        return x * 3;
    };

    TEST_ASSERT_OP(fold_res(0), ==, 0);
    TEST_ASSERT_OP(fold_res(1), ==, 3);
    TEST_ASSERT_OP(fold_res(2), ==, 6);
    TEST_ASSERT_OP(fold_res(3), ==, 9);

    (void)h_triple;

    return 0;
}
