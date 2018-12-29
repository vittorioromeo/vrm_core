#include "../../utils/test_utils.hpp"
#include <vector>
#include <vrm/core/for_args/for_args_complete.hpp>

using namespace vrm::core;

void test_empty_for()
{
    std::vector<sz_t> iterations, arg_indices;

    // Assume arity is 1, if not specified.
    // Assume `continue_t` is returned, if return type is `void`.
    auto empty_for = static_for([&](auto metadata, auto) {
        iterations.emplace_back(metadata.iteration());
        arg_indices.emplace_back(metadata.arg_index());
    });

    using empty_for_t = decltype(empty_for);
    static_assert(empty_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r0 = empty_for(0);
        SA_TYPE((unwrap(r0)), (no_return));

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[0], ==, 0);
    }

    {
        iterations.clear();
        arg_indices.clear();

        auto r1 = empty_for(0, 1, 2, 3, 4);
        SA_TYPE((unwrap(r1)), (no_return));

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(iterations[1], ==, 1);
        TEST_ASSERT_OP(iterations[2], ==, 2);
        TEST_ASSERT_OP(iterations[3], ==, 3);
        TEST_ASSERT_OP(iterations[4], ==, 4);

        TEST_ASSERT_OP(arg_indices[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[1], ==, 1);
        TEST_ASSERT_OP(arg_indices[2], ==, 2);
        TEST_ASSERT_OP(arg_indices[3], ==, 3);
        TEST_ASSERT_OP(arg_indices[4], ==, 4);
    }
}

void test_unary_for()
{
    std::vector<sz_t> iterations, arg_indices;

    auto unary_for = static_for([&](auto metadata, auto x) {
        iterations.emplace_back(metadata.iteration());
        arg_indices.emplace_back(metadata.arg_index());
        return metadata.continue_(x);
    });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(0);
        SA_TYPE((unwrap(r)), (int));

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[0], ==, 0);
    }

    {
        iterations.clear();
        arg_indices.clear();

        auto r1 = unary_for(0, 1, 2, 3, 4);
        SA_TYPE((unwrap(r1)), (int));

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(iterations[1], ==, 1);
        TEST_ASSERT_OP(iterations[2], ==, 2);
        TEST_ASSERT_OP(iterations[3], ==, 3);
        TEST_ASSERT_OP(iterations[4], ==, 4);

        TEST_ASSERT_OP(arg_indices[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[1], ==, 1);
        TEST_ASSERT_OP(arg_indices[2], ==, 2);
        TEST_ASSERT_OP(arg_indices[3], ==, 3);
        TEST_ASSERT_OP(arg_indices[4], ==, 4);
    }
}

void test_unary_for_break()
{
    std::vector<sz_t> iterations, arg_indices;

    auto unary_for = static_for([&](auto metadata, auto x) {
        iterations.emplace_back(metadata.iteration());
        arg_indices.emplace_back(metadata.arg_index());

        // Break when `3` is found, and return it.
        if constexpr(bool_v<(x == 3)>)
        {
            return metadata.break_(x);
        }
        else
        {
            return metadata.continue_(x);
        }
    });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(
            int_v<0>, int_v<1>, int_v<2>, int_v<3>, int_v<4>, int_v<5>);

        SA_TYPE((unwrap(r)), (int_<3>));

        TEST_ASSERT_OP(iterations.size(), ==, 4);
        TEST_ASSERT_OP(arg_indices.size(), ==, 4);

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(iterations[1], ==, 1);
        TEST_ASSERT_OP(iterations[2], ==, 2);
        TEST_ASSERT_OP(iterations[3], ==, 3);

        TEST_ASSERT_OP(arg_indices[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[1], ==, 1);
        TEST_ASSERT_OP(arg_indices[2], ==, 2);
        TEST_ASSERT_OP(arg_indices[3], ==, 3);
    }

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(
            int_v<0>, int_v<1>, int_v<2>, int_v<1>, int_v<2>, int_v<5>);

        SA_TYPE((unwrap(r)), (int_<5>));

        TEST_ASSERT_OP(iterations.size(), ==, 6);
        TEST_ASSERT_OP(arg_indices.size(), ==, 6);

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(iterations[1], ==, 1);
        TEST_ASSERT_OP(iterations[2], ==, 2);
        TEST_ASSERT_OP(iterations[3], ==, 3);
        TEST_ASSERT_OP(iterations[4], ==, 4);
        TEST_ASSERT_OP(iterations[5], ==, 5);

        TEST_ASSERT_OP(arg_indices[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[1], ==, 1);
        TEST_ASSERT_OP(arg_indices[2], ==, 2);
        TEST_ASSERT_OP(arg_indices[3], ==, 3);
        TEST_ASSERT_OP(arg_indices[4], ==, 4);
        TEST_ASSERT_OP(arg_indices[5], ==, 5);
    }
}

void test_unary_for_skip()
{
    std::vector<sz_t> iterations, arg_indices;

    auto unary_for = static_for([&](auto metadata, auto x) {
        iterations.emplace_back(metadata.iteration());
        arg_indices.emplace_back(metadata.arg_index());

        // Skip one argument when `-1` is found
        if constexpr(bool_v<(x == -1)>)
        {
            return metadata.skip(sz_t_v<1>, x);
        }
        else
        {
            return metadata.continue_(x);
        }
    });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(int_v<0>, int_v<1>, int_v<-1>, int_v<2>, int_v<3>,
            int_v<-1>, int_v<4>, int_v<5>);

        SA_TYPE((unwrap(r)), (int_<5>));

        // Two iterations are skipped.
        TEST_ASSERT_OP(iterations.size(), ==, 6);
        TEST_ASSERT_OP(arg_indices.size(), ==, 6);

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(iterations[1], ==, 1);
        TEST_ASSERT_OP(iterations[2], ==, 2);
        TEST_ASSERT_OP(iterations[3], ==, 3);
        TEST_ASSERT_OP(iterations[4], ==, 4);
        TEST_ASSERT_OP(iterations[5], ==, 5);

        TEST_ASSERT_OP(arg_indices[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[1], ==, 1);
        TEST_ASSERT_OP(arg_indices[2], ==, 2);
        // Skip 3.
        TEST_ASSERT_OP(arg_indices[3], ==, 4);
        TEST_ASSERT_OP(arg_indices[4], ==, 5);
        // Skip 6.
        TEST_ASSERT_OP(arg_indices[5], ==, 7);
    }
}

void test_unary_for_accumulate()
{
    std::vector<sz_t> iterations, arg_indices;

    auto unary_for = static_for([&](auto metadata, auto x) {
        iterations.emplace_back(metadata.iteration());
        arg_indices.emplace_back(metadata.arg_index());

        // Skip one argument when `-1` is found
        if constexpr(metadata.has_no_return())
        {
            static_assert(!is_int_constant<decltype(unwrap(metadata))>{});
            static_assert(std::is_same_v<decltype(unwrap(metadata)), no_return>);
            static_assert(is_int_constant<decltype(x)>{});

            // Base case.
            return metadata.continue_(x);
        }
        else
        {
            static_assert(is_int_constant<decltype(unwrap(metadata))>{});
            static_assert(is_int_constant<decltype(x)>{});

            // "Recursive" case.
            // Sum with previous return type.
            return metadata.continue_(int_v<unwrap(metadata) + x>);
        }
    });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1);

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(int_v<1>, int_v<2>, int_v<3>);
        SA_TYPE((unwrap(r)), (int_<6>));

        // Two iterations are skipped.
        TEST_ASSERT_OP(iterations.size(), ==, 3);
        TEST_ASSERT_OP(arg_indices.size(), ==, 3);

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(iterations[1], ==, 1);
        TEST_ASSERT_OP(iterations[2], ==, 2);

        TEST_ASSERT_OP(arg_indices[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[1], ==, 1);
        TEST_ASSERT_OP(arg_indices[2], ==, 2);
    }
}

void test_unary_for_accumulate2()
{
    auto static_accumulator = static_for([](auto mx, auto x) {
        if constexpr(mx.has_no_return())
        {
            return mx.continue_(x);
        }
        else
        {
            return mx.continue_(int_v<unwrap(mx) + x>);
        }
    });

    SA_TYPE(                                                        // .
        (unwrap(static_accumulator(int_v<1>, int_v<1>, int_v<1>))), // .
        (int_<1 + 1 + 1>));

    SA_TYPE(                                                        // .
        (unwrap(static_accumulator(int_v<1>, int_v<2>, int_v<3>))), // .
        (int_<1 + 2 + 3>));

    SA_TYPE(                                                // .
        (unwrap(static_accumulator(int_v<10>, int_v<20>))), // .
        (int_<10 + 20>));
}

void test_unary_for_accumulate_binary()
{
    auto static_b_acc = static_for<2>([](auto mx, auto x0, auto x1) {
        if constexpr(mx.has_no_return())
        {
            return mx.continue_with(x0, x1);
        }
        else
        {
            auto l0 = unwrap<0>(mx);
            auto l1 = unwrap<1>(mx);

            return mx.continue_with(int_v<l0 + x0>, int_v<l1 + x1>);
        }
    });

    auto r = static_b_acc(   // .
        int_v<1>, int_v<10>, // .
        int_v<2>, int_v<10>, // .
        int_v<3>, int_v<10>, // .
        int_v<4>, int_v<10>);

    static_assert(decltype(unwrap<0>(r)){} == int_v<1 + 2 + 3 + 4>, "");
    static_assert(decltype(unwrap<1>(r)){} == int_v<10 + 10 + 10 + 10>, "");
}

TEST_MAIN()
{
    test_empty_for();
    test_unary_for();
    test_unary_for_break();
    test_unary_for_skip();
    test_unary_for_accumulate();
    test_unary_for_accumulate2();
    test_unary_for_accumulate_binary();

    // TODO: test accumulation
    // TODO: test other arities

    return 0;
}
