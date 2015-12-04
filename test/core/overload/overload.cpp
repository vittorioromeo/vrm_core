#include "../../utils/test_utils.hpp"
#include <cstddef>
#include <vrm/core/config.hpp>
#include <vrm/core/overload.hpp>

struct Trad
{
    int val = 0;

    auto operator()(int) { return 1; }
    auto operator()(float) { return 2; }
    auto operator()(double) { return 3; }
    auto operator()(std::nullptr_t) { return val++; }
};

int main()
{
    TEST_ASSERT_OP(Trad{}(2), ==, 1);
    TEST_ASSERT_OP(Trad{}(2.f), ==, 2);
    TEST_ASSERT_OP(Trad{}(2.0), ==, 3);
    TEST_ASSERT_OP(Trad{}(nullptr), ==, 0);
    TEST_ASSERT_OP(Trad{}(nullptr), ==, 0);

    auto t = Trad{};
    TEST_ASSERT_OP(t(nullptr), ==, 0);
    TEST_ASSERT_OP(t(nullptr), ==, 1);
    TEST_ASSERT_OP(t(nullptr), ==, 2);
    TEST_ASSERT_OP(t(nullptr), ==, 3);

    using namespace vrm::core;

    auto movrl = make_overload(
        [](int)
        {
            return 1;
        },
        [](float)
        {
            return 2;
        },
        [](double)
        {
            return 3;
        },
        [val = 0](std::nullptr_t) mutable
        {
            return val++;
        });

    TEST_ASSERT_OP(movrl(2), ==, 1);
    TEST_ASSERT_OP(movrl(2.f), ==, 2);
    TEST_ASSERT_OP(movrl(2.0), ==, 3);
    TEST_ASSERT_OP(movrl(nullptr), ==, 0);
    TEST_ASSERT_OP(movrl(nullptr), ==, 1);
    TEST_ASSERT_OP(movrl(nullptr), ==, 2);
    TEST_ASSERT_OP(movrl(nullptr), ==, 3);

    auto tpl_ov = make_overload(
        [](int)
        {
            return 1;
        },
        [](auto)
        {
            return 2;
        });

    TEST_ASSERT_OP(tpl_ov(0), ==, 1);
    TEST_ASSERT_OP(tpl_ov(int{}), ==, 1);
    TEST_ASSERT_OP(tpl_ov(0.f), ==, 2);
    TEST_ASSERT_OP(tpl_ov(float{}), ==, 2);

    return 0;
}
