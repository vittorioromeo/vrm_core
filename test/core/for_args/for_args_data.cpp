#include "../../utils/test_utils.hpp"
#include <vrm/core/for_args/for_args_data.hpp>

int main()
{
    using namespace vrm::core;

    {
        int acc{0};
        for_args_data(
            [&acc](auto data, auto x)
            {
                TEST_ASSERT_OP(
                    decltype(data)::index, ==, static_cast<std::size_t>(x));
                acc += x;
            },
            0, 1, 2, 3, 4, 5);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));
    }

    {
        int acc{0};
        for_args_data(
            [&acc](auto data, auto&& x)
            {
                TEST_ASSERT_OP(
                    decltype(data)::index, ==, static_cast<std::size_t>(x));
                acc += x;
            },
            0, 1, 2, 3, 4, 5);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));
    }

    {
        int steps = 0;
        int ctrl = 0;

        auto a = [&steps, &ctrl]
        {
            ++steps;
            ctrl = 1;
            return 1;
        };
        auto b = [&steps, &ctrl]
        {
            ++steps;
            ctrl = 2;
            return 2;
        };
        auto c = [&steps, &ctrl]
        {
            ++steps;
            ctrl = 3;
            return 3;
        };
        auto d = [&steps, &ctrl]
        {
            ++steps;
            ctrl = 4;
            return 4;
        };
        auto e = [&steps, &ctrl]
        {
            ++steps;
            ctrl = 5;
            return 5;
        };

        int acc{0};
        for_args_data([&, lastidx = 0 ](auto data, auto x) mutable
            {
                TEST_ASSERT_OP(decltype(data)::index, ==, (std::size_t)lastidx);
                ++lastidx;

                auto val(x());
                acc += val;

                if(steps == 1) TEST_ASSERT_OP(ctrl, ==, 2);
                if(steps == 2) TEST_ASSERT_OP(ctrl, ==, 1);
                if(steps == 3) TEST_ASSERT_OP(ctrl, ==, 4);
                if(steps == 4) TEST_ASSERT_OP(ctrl, ==, 3);
                if(steps == 5) TEST_ASSERT_OP(ctrl, ==, 5);
            },
            b, a, d, c, e);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));
    }

    {
        int acc{0};
        for_args_data<1>([&acc, lastidx = 0 ](auto data, auto x) mutable
            {
                TEST_ASSERT_OP(decltype(data)::index, ==, (std::size_t)lastidx);
                ++lastidx;
                acc += x;
            },
            0, 1, 2, 3, 4, 5);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));

        acc = 0;
        for_args_data<1>([&acc, lastidx = 0 ](auto data, auto&& x) mutable
            {
                TEST_ASSERT_OP(decltype(data)::index, ==, (std::size_t)lastidx);
                ++lastidx;
                acc += x;
            },
            0, 1, 2, 3, 4, 5);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));
    }

    {
        int acc{0};
        for_args_data<2>([&acc, lastidx = 0 ](auto data, auto x, auto y) mutable
            {
                TEST_ASSERT_OP(decltype(data)::index, ==, (std::size_t)lastidx);
                ++lastidx;
                acc += x + y;
            },
            0, 1, 2, 3, 4, 5);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));

        acc = 0;
        for_args_data<2>(
            [&acc, lastidx = 0 ](auto data, auto&& x, auto&& y) mutable
            {
                TEST_ASSERT_OP(decltype(data)::index, ==, (std::size_t)lastidx);
                ++lastidx;
                acc += x + y;
            },
            0, 1, 2, 3, 4, 5);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));
    }

    {
        int acc{0};
        for_args_data<3>(
            [&acc, lastidx = 0 ](auto data, auto x, auto y, auto z) mutable
            {
                TEST_ASSERT_OP(decltype(data)::index, ==, (std::size_t)lastidx);
                ++lastidx;
                acc += x + y + z;
            },
            0, 1, 2, 3, 4, 5);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));

        acc = 0;
        for_args_data<3>([&acc, lastidx = 0 ](
                             auto data, auto&& x, auto&& y, auto&& z) mutable
            {
                TEST_ASSERT_OP(decltype(data)::index, ==, (std::size_t)lastidx);
                ++lastidx;
                acc += x + y + z;
            },
            0, 1, 2, 3, 4, 5);
        TEST_ASSERT_OP(acc, ==, (0 + 1 + 2 + 3 + 4 + 5));
    }
}
