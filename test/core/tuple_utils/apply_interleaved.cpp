#include "../../utils/test_utils.hpp"
#include <vrm/core/config.hpp>
#include <vrm/core/tuple_utils/apply.hpp>

struct noncopy
{
    int x = 0;
    noncopy(int xxx) : x{xxx}
    {
    }

    noncopy(const noncopy&) = delete;
    noncopy& operator=(const noncopy&) = delete;

    noncopy(noncopy&&) = default;
    noncopy& operator=(noncopy&&) = default;

    bool operator==(const noncopy& y) const
    {
        return x == y.x;
    }
};

using namespace vrm::core;

auto first = [](auto&& x, auto&&...) -> const auto &
{
    return x;
};
auto second = [](auto&&, auto&& x, auto&&...) -> const auto &
{
    return x;
};
auto count = [](auto&&... xs)
{
    return sizeof...(xs);
};
auto binary_append_fst = [](auto a, auto b, auto&&...)
{
    return a + b;
};
auto binary_append_snd = [](auto, auto, auto a, auto b)
{
    return a + b;
};


void TEST_CONST noncopy_test()
{
    {
        auto t0 = std::make_tuple(noncopy{0}, 'a');
        auto t1 = std::make_tuple(noncopy{1}, 'b');

        TEST_ASSERT_OP(apply(first, t0).x, ==, 0);
        TEST_ASSERT_OP(apply(first, t1).x, ==, 1);
        //  TEST_ASSERT_OP(apply(second, t0), ==, 'a');
        //  TEST_ASSERT_OP(apply(second, t1), ==, 'b');
    }

    {
        auto t0 = std::make_tuple(noncopy{0}, 'a');
        auto t1 = std::make_tuple(noncopy{1}, 'b');

        auto v = apply_all_sequential(first, std::move(t0), std::move(t1)).x;
        TEST_ASSERT_OP(v, ==, 0);
    }

    {
        auto t0 = std::make_tuple(noncopy{0}, 'a');
        auto t1 = std::make_tuple(noncopy{1}, 'b');

        auto v = apply_all_sequential(second, std::move(t0), std::move(t1));
        TEST_ASSERT_OP(v, ==, 'a');
    }

    {
        auto t0 = std::make_tuple(noncopy{0}, 'a');
        auto t1 = std::make_tuple(noncopy{1}, 'b');

        auto v =
            apply_all_interleaved<2>(first, std::move(t0), std::move(t1)).x;
        TEST_ASSERT_OP(v, ==, 0);
    }

    {
        auto t0 = std::make_tuple(noncopy{0}, 'a');
        auto t1 = std::make_tuple(noncopy{1}, 'b');

        auto v =
            apply_all_interleaved<2>(second, std::move(t0), std::move(t1)).x;
        TEST_ASSERT_OP(v, ==, 1);
    }
}

int main()
{
    auto t0 = std::make_tuple(0, 'a', 1, 'b');
    auto t1 = std::make_tuple(2, 'c', 3, 'd');

    TEST_ASSERT_OP(apply(first, t0), ==, 0);
    TEST_ASSERT_OP(apply(first, t1), ==, 2);
    TEST_ASSERT_OP(apply(second, t0), ==, 'a');
    TEST_ASSERT_OP(apply(second, t1), ==, 'c');

    TEST_ASSERT_OP(apply_interleaved<2>(first, t0), ==, 0);
    TEST_ASSERT_OP(apply_interleaved<2>(first, t1), ==, 2);
    TEST_ASSERT_OP(apply_interleaved<2>(second, t0), ==, 1);
    TEST_ASSERT_OP(apply_interleaved<2>(second, t1), ==, 3);

    TEST_ASSERT_OP(apply(count, t0), ==, 4);
    TEST_ASSERT_OP(apply(count, t1), ==, 4);

    TEST_ASSERT_OP(apply_interleaved<2>(count, t0), ==, 4);
    TEST_ASSERT_OP(apply_interleaved<2>(count, t1), ==, 4);

    TEST_ASSERT_OP(apply_all_interleaved<1>(count, t0, t1), ==, 8);
    TEST_ASSERT_OP(apply_all_interleaved<2>(count, t0, t1), ==, 8);
    TEST_ASSERT_OP(apply_all_interleaved<4>(count, t0, t1), ==, 8);
    TEST_ASSERT_OP(apply_all_interleaved<8>(count, t0, t1), ==, 8);

    TEST_ASSERT_OP(apply_interleaved<2>(binary_append_fst, t0), ==, 0 + 1);
    TEST_ASSERT_OP(apply_interleaved<2>(binary_append_fst, t1), ==, 2 + 3);

    TEST_ASSERT_OP(apply_interleaved<2>(binary_append_snd, t0), ==, 'a' + 'b');
    TEST_ASSERT_OP(apply_interleaved<2>(binary_append_snd, t1), ==, 'c' + 'd');

    noncopy_test();
    return 0;
}
