#include "../../utils/test_utils.hpp"
#include <vector>
#include <vrm/core/for_args/for_args_complete.hpp>

using namespace vrm::core;

void test_empty_for()
{
    std::vector<sz_t> iterations, arg_indices;

    // Assume arity is 1, if not specified.
    // Assume `continue_t` is returned, if return type is `void`.
    auto empty_for = static_for_args([&](auto metadata, auto)
        {
            iterations.emplace_back(decltype(metadata)::iteration());
        });

    using empty_for_t = decltype(empty_for);
    static_assert(empty_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r0 = empty_for(0);
        using r0_unwrap = decltype(r0)::unwrap;
        SA_SAME((r0_unwrap), (no_return));

        TEST_ASSERT_OP(iterations[0], ==, 0);

        // TODO: arg indices
    }
    {

        iterations.clear();
        arg_indices.clear();

        auto r1 = empty_for(0, 1, 2, 3, 4);
        using r1_unwrap = decltype(r1)::unwrap;
        SA_SAME((r1_unwrap), (no_return));

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(iterations[1], ==, 1);
        TEST_ASSERT_OP(iterations[2], ==, 2);
        TEST_ASSERT_OP(iterations[3], ==, 3);
        TEST_ASSERT_OP(iterations[4], ==, 4);

        // TODO: arg indices
    }
}

void test_unary_for()
{
    auto unary_for = static_for_args([](auto, auto x)
        {
            return static_for_continue(x);
        });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    auto r0 = unary_for(0);
    using r0_unwrap = decltype(r0)::unwrap;
    SA_SAME((r0_unwrap), (int));

    auto r1 = unary_for(0, 1, 2, 3, 4);
    using r1_unwrap = decltype(r1)::unwrap;
    SA_SAME((r1_unwrap), (int));
}

int main()
{
    test_empty_for();
    test_unary_for();

    // TODO: test accumulation
    // TODO: test other arities

    return 0;
}
