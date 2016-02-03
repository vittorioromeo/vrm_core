#include "../../utils/test_utils.hpp"
#include <cstddef>
#include <vrm/core/config.hpp>
#include <vrm/core/static_if.hpp>

struct banana
{
};

struct apple
{
};

struct chestnut
{
};

template <typename T>
using is_banana = std::integral_constant<bool, std::is_same<banana, T>{}>;

template <typename T>
using is_apple = std::integral_constant<bool, std::is_same<apple, T>{}>;

template <typename T>
auto eat_fruit(T fruit)
{
    return vrm::core::static_if(is_banana<T>{})
        .then([](auto&)
            {
                return 0;
            })
        .else_if(is_apple<T>{})
        .then([](auto&)
            {
                return 10.f;
            })
        .else_([](auto&)
            {
                return 'x';
            })(fruit);
}
TEST_MAIN()
{
    auto b = eat_fruit(banana{});
    auto a = eat_fruit(apple{});
    auto c = eat_fruit(chestnut{});

    static_assert(std::is_same<decltype(b), int>{}, "");
    static_assert(std::is_same<decltype(a), float>{}, "");
    static_assert(std::is_same<decltype(c), char>{}, "");

    TEST_ASSERT_OP(b, ==, 0);
    TEST_ASSERT_OP(a, ==, 10.f);
    TEST_ASSERT_OP(c, ==, 'x');

    return 0;
}
