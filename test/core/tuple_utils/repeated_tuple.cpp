#include "../../utils/test_utils.hpp"
#include <vrm/core/detection.hpp>
#include <vrm/core/tuple_utils/for.hpp>
#include <vrm/core/tuple_utils/repeated_tuple.hpp>

int main()
{
    using namespace vrm::core;

    using r0_type = repeated_tuple<5, int>;

    static_assert(
        std::is_same<r0_type, std::tuple<int, int, int, int, int>>{}, "");

    auto r1 = make_repeated_tuple<6>(10.f);

    int n = 0;
    for_tuple(
        [&](const auto& x)
        {
            ++n;
            TEST_ASSERT_OP(x, ==, 10.f);
        },
        r1);

    TEST_ASSERT_OP(n, ==, 6);

    return 0;
}