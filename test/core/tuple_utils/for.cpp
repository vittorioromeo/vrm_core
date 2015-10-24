#include "../../utils/test_utils.hpp"
#include <vrm/core/config.hpp>
#include <vrm/core/tuple_utils/for.hpp>

int main()
{
    auto t0 = std::make_tuple(0, 1, 2, 3);
    auto t1 = std::make_tuple(10.f, 25.0, 'b');
    auto t2 = std::make_tuple('a', 1, 3);

    auto id = [](auto&& x)
    {
        return x;
    };

    std::size_t last_index = 0;
    vrm::core::for_tuple_data(
        [&](auto data, auto&& y)
        {
            TEST_ASSERT_OP(decltype(data)::index, ==, last_index);
            ++last_index;

            TEST_ASSERT_OP(y, ==, id(std::get<decltype(data)::index>(t0)));
        },
        t0);

    last_index = 0;
    vrm::core::for_tuple_data(
        [&](auto data, auto&& y)
        {
            TEST_ASSERT_OP(decltype(data)::index, ==, last_index);
            ++last_index;

            TEST_ASSERT_OP(y, ==, id(std::get<decltype(data)::index>(t1)));
        },
        t1);

    last_index = 0;
    vrm::core::for_tuple_data(
        [&](auto data, auto&& y)
        {
            TEST_ASSERT_OP(decltype(data)::index, ==, last_index);
            ++last_index;

            TEST_ASSERT_OP(y, ==, id(std::get<decltype(data)::index>(t2)));
        },
        t2);

    int acc = 0;
    vrm::core::for_tuple(
        [&](auto x)
        {
            acc += x;
        },
        std::make_tuple(100, 10, 1));
    TEST_ASSERT_OP(acc, ==, 111);

    int acc2 = 0;
    vrm::core::for_tuple(
        [&](auto x, auto y)
        {
            acc2 += (x / y);
        },
        std::make_tuple(100, 100, 100), std::make_tuple(1, 10, 50));
    TEST_ASSERT_OP(acc2, ==, (100 / 1 + 100 / 10 + 100 / 50));

    return 0;
}