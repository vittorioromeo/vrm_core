#include "../../../utils/test_res_utils.hpp"
#include <vrm/core/experimental/sparse_set.hpp>

using ss_type = vrm::core::fixed_vector_sparse_set<unsigned int, 100>;

void t0()
{
    ss_type ss;

    TEST_ASSERT(ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 0);

    for(auto i = 0; i < 100; ++i)
    {
        TEST_ASSERT(!ss.has(i));
    }

    TEST_ASSERT(ss.add(0) == true);
    TEST_ASSERT(ss.add(0) == false);

    TEST_ASSERT(!ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 1);

    TEST_ASSERT(ss.has(0));

    {
        int acc = 0;
        for(auto x : ss) acc += x;
        TEST_ASSERT_OP(acc, ==, 0);
    }

    TEST_ASSERT(ss.add(5) == true);
    TEST_ASSERT(ss.add(10) == true);
    TEST_ASSERT(ss.add(20) == true);

    auto t_after_fill = [](const auto& x_ss)
    {
        TEST_ASSERT(!x_ss.empty());
        TEST_ASSERT_OP(x_ss.size(), ==, 4);

        TEST_ASSERT(x_ss.has(0));
        TEST_ASSERT(!x_ss.has(1));
        TEST_ASSERT(!x_ss.has(2));
        TEST_ASSERT(!x_ss.has(3));
        TEST_ASSERT(!x_ss.has(4));
        TEST_ASSERT(x_ss.has(5));
        TEST_ASSERT(x_ss.has(10));
        TEST_ASSERT(x_ss.has(20));
        TEST_ASSERT(!x_ss.has(99));

        {
            int acc = 0;
            for(auto x : x_ss) acc += x;
            TEST_ASSERT_OP(acc, ==, (0 + 5 + 10 + 20));
        }
    };

    t_after_fill(ss);

    TEST_ASSERT_OP(ss.back(), ==, 20);
    ss.pop_back();
    TEST_ASSERT(!ss.has(20));
    TEST_ASSERT_OP(ss.back(), ==, 10);

    TEST_ASSERT(ss.erase(11) == false);

    TEST_ASSERT(ss.has(0));
    TEST_ASSERT(ss.erase(0) == true);
    TEST_ASSERT(!ss.has(0));
    TEST_ASSERT(ss.erase(0) == false);

    TEST_ASSERT(ss.has(10));
    TEST_ASSERT(ss.erase(10) == true);
    TEST_ASSERT(!ss.has(10));
    TEST_ASSERT(ss.erase(10) == false);

    ss.clear();

    TEST_ASSERT(ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 0);

    for(auto i = 0; i < 100; ++i)
    {
        TEST_ASSERT(!ss.has(i));
    }

    TEST_ASSERT(ss.add(0) == true);
}


void t1()
{
    ss_type ss;

    TEST_ASSERT(ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 0);

    for(auto i = 0; i < 100; ++i)
    {
        TEST_ASSERT(!ss.has(i));
    }

    TEST_ASSERT(ss.add(0) == true);
    TEST_ASSERT(ss.add(0) == false);

    TEST_ASSERT(!ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 1);

    TEST_ASSERT(ss.has(0));

    {
        int acc = 0;
        for(auto x : ss) acc += x;
        TEST_ASSERT_OP(acc, ==, 0);
    }

    TEST_ASSERT(ss.add(5) == true);
    TEST_ASSERT(ss.add(10) == true);
    TEST_ASSERT(ss.add(20) == true);

    auto t_after_fill = [](const auto& x_ss)
    {
        TEST_ASSERT(!x_ss.empty());
        TEST_ASSERT_OP(x_ss.size(), ==, 4);

        TEST_ASSERT(x_ss.has(0));
        TEST_ASSERT(!x_ss.has(1));
        TEST_ASSERT(!x_ss.has(2));
        TEST_ASSERT(!x_ss.has(3));
        TEST_ASSERT(!x_ss.has(4));
        TEST_ASSERT(x_ss.has(5));
        TEST_ASSERT(x_ss.has(10));
        TEST_ASSERT(x_ss.has(20));
        TEST_ASSERT(!x_ss.has(99));

        {
            int acc = 0;
            for(auto x : x_ss) acc += x;
            TEST_ASSERT_OP(acc, ==, (0 + 5 + 10 + 20));
        }
    };

    t_after_fill(ss);
    ss_type ss2 = std::move(ss);
    t_after_fill(ss2);

    TEST_ASSERT_OP(ss2.back(), ==, 20);
    ss2.pop_back();
    TEST_ASSERT(!ss2.has(20));
    TEST_ASSERT_OP(ss2.back(), ==, 10);

    TEST_ASSERT(ss2.erase(11) == false);

    TEST_ASSERT(ss2.has(0));
    TEST_ASSERT(ss2.erase(0) == true);
    TEST_ASSERT(!ss2.has(0));
    TEST_ASSERT(ss2.erase(0) == false);

    TEST_ASSERT(ss2.has(10));
    TEST_ASSERT(ss2.erase(10) == true);
    TEST_ASSERT(!ss2.has(10));
    TEST_ASSERT(ss2.erase(10) == false);

    ss2.clear();

    TEST_ASSERT(ss2.empty());
    TEST_ASSERT_OP(ss2.size(), ==, 0);

    for(auto i = 0; i < 100; ++i)
    {
        TEST_ASSERT(!ss2.has(i));
    }

    TEST_ASSERT(ss2.add(0) == true);
}

void t2()
{
    ss_type ss;

    TEST_ASSERT(ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 0);

    TEST_ASSERT(ss.add(0) == true);
    TEST_ASSERT(ss.add(0) == false);
    TEST_ASSERT(ss.add(0) == false);

    TEST_ASSERT(!ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 1);
    TEST_ASSERT(ss.has(0));
    TEST_ASSERT(!ss.has(1));
    TEST_ASSERT(!ss.has(2));

    TEST_ASSERT(ss.add(1) == true);
    TEST_ASSERT(ss.add(1) == false);

    TEST_ASSERT(!ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 2);
    TEST_ASSERT(ss.has(0));
    TEST_ASSERT(ss.has(1));
    TEST_ASSERT(!ss.has(2));

    TEST_ASSERT(ss.add(2) == true);
    TEST_ASSERT(ss.add(2) == false);

    TEST_ASSERT(!ss.empty());
    TEST_ASSERT_OP(ss.size(), ==, 3);
    TEST_ASSERT(ss.has(0));
    TEST_ASSERT(ss.has(1));
    TEST_ASSERT(ss.has(2));
}

TEST_MAIN()
{
    t0();
    t1();
    t2();
}
