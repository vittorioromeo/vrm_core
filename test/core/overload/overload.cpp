#include "../../utils/test_utils.hpp"
#include <vrm/core/config.hpp>
#include <vrm/core/overload.hpp>

struct Trad
{
    auto operator()(int) { return 1; }
    auto operator()(float) { return 2; }
    auto operator()(double) { return 3; }
};

int main()
{
    TEST_ASSERT_OP(Trad{}(2), ==, 1);
    TEST_ASSERT_OP(Trad{}(2.f), ==, 2);
    TEST_ASSERT_OP(Trad{}(2.0), ==, 3);

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
        });

    TEST_ASSERT_OP(movrl(2), ==, 1);
    TEST_ASSERT_OP(movrl(2.f), ==, 2);
    TEST_ASSERT_OP(movrl(2.0), ==, 3);

    return 0;
}