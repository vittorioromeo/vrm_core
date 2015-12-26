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

void unsub_test0()
{
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
}

void unsub_test1()
{
    int f0 = 0;
    int f1 = 0;
    int f2 = 0;
    int f3 = 0;

    auto reset = [&]
    {
        f0 = f1 = f2 = f3 = 0;
    };

    auto test = [&](auto x0, auto x1, auto x2, auto x3)
    {
        std::cout << f0 << " " << f1 << " " << f2 << " " << f3 << "\n";

        TEST_ASSERT_OP(f0, ==, x0);
        TEST_ASSERT_OP(f1, ==, x1);
        TEST_ASSERT_OP(f2, ==, x2);
        TEST_ASSERT_OP(f3, ==, x3);

        reset();
    };

    test(0, 0, 0, 0);

    {
        dynamic_delegate<void()> d;

        auto s0 = d += [&]
        {
            f0 = 1;
        };
        auto s1 = d += [&]
        {
            f1 = 1;
        };
        auto s2 = d += [&]
        {
            f2 = 1;
        };
        auto s3 = d += [&]
        {
            f3 = 1;
        };

        d();
        test(1, 1, 1, 1);

        d -= s0;
        d();
        test(0, 1, 1, 1);

        d -= s3;
        d();
        test(0, 1, 1, 0);

        d -= s1;
        d();
        test(0, 0, 1, 0);

        d -= s2;
        d();
        test(0, 0, 0, 0);
    }

    {
        dynamic_delegate<void()> d;

        auto s0 = d += [&]
        {
            f0 = 1;
        };
        auto s1 = d += [&]
        {
            f1 = 1;
        };
        auto s2 = d += [&]
        {
            f2 = 1;
        };
        auto s3 = d += [&]
        {
            f3 = 1;
        };

        d();
        test(1, 1, 1, 1);

        d -= s0;
        d();
        test(0, 1, 1, 1);

        d -= s1;
        d();
        test(0, 0, 1, 1);

        d -= s2;
        d();
        test(0, 0, 0, 1);

        d -= s3;
        d();
        test(0, 0, 0, 0);
    }

    {
        dynamic_delegate<void()> d;

        auto s0 = d += [&]
        {
            f0 = 1;
        };
        auto s1 = d += [&]
        {
            f1 = 1;
        };
        auto s2 = d += [&]
        {
            f2 = 1;
        };
        auto s3 = d += [&]
        {
            f3 = 1;
        };

        d();
        test(1, 1, 1, 1);

        d -= s3;
        d();
        test(1, 1, 1, 0);

        d -= s2;
        d();
        test(1, 1, 0, 0);

        d -= s1;
        d();
        test(1, 0, 0, 0);

        d -= s0;
        d();
        test(0, 0, 0, 0);
    }
}

void unsub_test2()
{
    dynamic_delegate<int(int)> d;
    auto h_adder = d += [](int x)
    {
        return x + 1;
    };
    auto h_doubler = d += [](int x)
    {
        return x * 2;
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
}

int main()
{
    prev_tests();
    unsub_test0();
    unsub_test1();
    unsub_test2();

    return 0;
}
