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
            iterations.emplace_back(metadata.iteration());
            arg_indices.emplace_back(metadata.arg_index());
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
        TEST_ASSERT_OP(arg_indices[0], ==, 0);
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

    auto unary_for = static_for_args([&](auto metadata, auto x)
        {
            iterations.emplace_back(metadata.iteration());
            arg_indices.emplace_back(metadata.arg_index());
            return static_for_continue(x);
        });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r0 = unary_for(0);
        using r0_unwrap = decltype(r0)::unwrap;
        SA_SAME((r0_unwrap), (int));

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[0], ==, 0);
    }

    {
        iterations.clear();
        arg_indices.clear();

        auto r1 = unary_for(0, 1, 2, 3, 4);
        using r1_unwrap = decltype(r1)::unwrap;
        SA_SAME((r1_unwrap), (int));

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

    auto unary_for = static_for_args([&](auto metadata, auto x)
        {
            iterations.emplace_back(metadata.iteration());
            arg_indices.emplace_back(metadata.arg_index());

            // Break when `3` is found, and return it.
            return static_if(bool_v<(x == 3)>)
                .then([](auto y)
                    {
                        return static_for_break(y);
                    })
                .else_([](auto y)
                    {
                        return static_for_continue(y);
                    })(x);
        });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(
            int_v<0>, int_v<1>, int_v<2>, int_v<3>, int_v<4>, int_v<5>);

        using r_unwrap = decltype(r)::unwrap;
        SA_SAME((r_unwrap), (int_<3>));

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

        using r_unwrap = decltype(r)::unwrap;
        SA_SAME((r_unwrap), (int_<5>));

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

    auto unary_for = static_for_args([&](auto metadata, auto x)
        {
            iterations.emplace_back(metadata.iteration());
            arg_indices.emplace_back(metadata.arg_index());

            // Skip one argument when `-1` is found
            return static_if(bool_v<(x == -1)>)
                .then([](auto y)
                    {
                        return static_for_skip<1>(y);
                    })
                .else_([](auto y)
                    {
                        return static_for_continue(y);
                    })(x);
        });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(int_v<0>, int_v<1>, int_v<-1>, int_v<2>, int_v<3>,
            int_v<-1>, int_v<4>, int_v<5>);

        using r_unwrap = decltype(r)::unwrap;
        SA_SAME((r_unwrap), (int_<5>));

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

    auto unary_for = static_for_args([&](auto metadata, auto x)
        {
            iterations.emplace_back(metadata.iteration());
            arg_indices.emplace_back(metadata.arg_index());

            // Skip one argument when `-1` is found
            return static_if(metadata.has_return())
                .then([](auto l, auto y)
                    {
                        static_assert(!is_int_constant<decltype(l)>{}, "");
                        static_assert(is_int_constant<decltype(y)>{}, "");

                        // Base case.
                        return static_for_continue(y);
                    })
                .else_([](auto l, auto y)
                    {
                        static_assert(is_int_constant<decltype(l)>{}, "");
                        static_assert(is_int_constant<decltype(y)>{}, "");

                        // "Recursive" case.
                        // Sum with previous return type.
                        return static_for_continue(int_v<l + y>);
                    })(metadata.last(), x);
        });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(int_v<1>, int_v<2>, int_v<3>);

        using r_unwrap = decltype(r)::unwrap;
        SA_SAME((r_unwrap), (int_<6>));

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


int main()
{
    test_empty_for();
    test_unary_for();
    test_unary_for_break();
    test_unary_for_skip();
    test_unary_for_accumulate();

    // TODO: test accumulation
    // TODO: test other arities

    return 0;
}
