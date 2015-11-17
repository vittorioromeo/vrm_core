#include "../../utils/test_utils.hpp"
#include <vrm/core/delegate.hpp>

int main()
{
    using namespace vrm::core;


    bool testState{false};
    delegate<void()> del1;
    del1 += [&testState]
    {
        testState = !testState;
    };

    del1();
    TEST_ASSERT(testState == true);
    del1();
    TEST_ASSERT(testState == false);

    delegate<int(int)> del2;
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

    delegate<void()> del3;
    del3 += [&del1]
    {
        del1();
    };
    del3();
    TEST_ASSERT(testState == true);

    delegate<void(int&)> del4;
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
        delegate<int()> del5;
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

    return 0;
}
