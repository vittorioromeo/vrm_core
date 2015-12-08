#include "../../utils/test_utils.hpp"
#include <vector>
#include <vrm/core/for_args/for_args_complete.hpp>

using namespace vrm::core;

void test_empty_for()
{
    std::vector<sz_t> iterations, arg_indices;

    // Assume arity is 1, if not specified.
    // Assume `continue_t` is returned, if return type is `void`.
    auto empty_for = static_for([&](auto metadata, auto)
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

    auto unary_for = static_for([&](auto metadata, auto x)
        {
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
        SA_TYPE((r()), (int));

        TEST_ASSERT_OP(iterations[0], ==, 0);
        TEST_ASSERT_OP(arg_indices[0], ==, 0);
    }

    {
        iterations.clear();
        arg_indices.clear();

        auto r1 = unary_for(0, 1, 2, 3, 4);
        SA_TYPE((r1()), (int));

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

    auto unary_for = static_for([&](auto metadata, auto x)
        {
            iterations.emplace_back(metadata.iteration());
            arg_indices.emplace_back(metadata.arg_index());

            // Break when `3` is found, and return it.
            return static_if(bool_v<(x == 3)>)
                .then([](auto m, auto y)
                    {
                        return m.break_(y);
                    })
                .else_([](auto m, auto y)
                    {
                        return m.continue_(y);
                    })(metadata, x);
        });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(
            int_v<0>, int_v<1>, int_v<2>, int_v<3>, int_v<4>, int_v<5>);

        SA_TYPE((r()), (int_<3>));

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

        SA_TYPE((r()), (int_<5>));

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

    auto unary_for = static_for([&](auto metadata, auto x)
        {
            iterations.emplace_back(metadata.iteration());
            arg_indices.emplace_back(metadata.arg_index());

            // Skip one argument when `-1` is found
            return static_if(bool_v<(x == -1)>)
                .then([](auto m, auto y)
                    {
                        return m.skip(sz_t_v<1>, y);
                    })
                .else_([](auto m, auto y)
                    {
                        return m.continue_(y);
                    })(metadata, x);
        });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(int_v<0>, int_v<1>, int_v<-1>, int_v<2>, int_v<3>,
            int_v<-1>, int_v<4>, int_v<5>);

        SA_TYPE((r()), (int_<5>));

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

    auto unary_for = static_for([&](auto metadata, auto x)
        {
            iterations.emplace_back(metadata.iteration());
            arg_indices.emplace_back(metadata.arg_index());

            // Skip one argument when `-1` is found
            return static_if(metadata.has_no_return())
                .then([](auto m, auto y)
                    {
                        static_assert(
                            !is_int_constant<decltype(m.last())>{}, "");

                        static_assert(
                            std::is_same<decltype(m.last()), no_return>{}, "");

                        static_assert(is_int_constant<decltype(y)>{}, "");

                        // Base case.
                        return m.continue_(y);
                    })
                .else_([](auto m, auto y)
                    {
                        static_assert(
                            is_int_constant<decltype(m.last())>{}, "");

                        static_assert(is_int_constant<decltype(y)>{}, "");

                        // "Recursive" case.
                        // Sum with previous return type.
                        return m.continue_(int_v<m.last() + y>);
                    })(metadata, x);
        });

    using unary_for_t = decltype(unary_for);
    static_assert(unary_for_t::arity == 1, "");

    {
        iterations.clear();
        arg_indices.clear();

        auto r = unary_for(int_v<1>, int_v<2>, int_v<3>);
        SA_TYPE((r()), (int_<6>));

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
    auto static_accumulator = static_for([](auto mx, auto x)
        {
            return static_if(mx.has_no_return())
                .then([](auto my, auto y)
                    {
                        return my.continue_(y);
                    })
                .else_([](auto my, auto y)
                    {
                        return my.continue_(int_v<my.last() + y>);
                    })(mx, x);
        });

    static_assert(                                                     // .
        decltype(static_accumulator(int_v<1>, int_v<1>, int_v<1>)()){} // .
            == int_v<1 + 1 + 1>,                                       // .
        "");

    static_assert(                                                     // .
        decltype(static_accumulator(int_v<1>, int_v<2>, int_v<3>)()){} // .
            == int_v<1 + 2 + 3>,                                       // .
        "");

    static_assert(                                             // .
        decltype(static_accumulator(int_v<10>, int_v<20>)()){} // .
            == int_v<10 + 20>,                                 // .
        "");
}

void test_unary_for_accumulate_binary()
{
    auto static_b_acc = static_for<2>([](auto mx, auto x0, auto x1)
        {
            return static_if(mx.has_no_return())
                .then([](auto my, auto y0, auto y1)
                    {
                        return my.continue_with(y0, y1);
                    })
                .else_([](auto my, auto y0, auto y1)
                    {
                        auto l0 = std::get<0>(my.last());
                        auto l1 = std::get<1>(my.last());

                        return my.continue_with(int_v<l0 + y0>, int_v<l1 + y1>);
                        // return my.continue_(int_v<my.last() + y>);
                    })(mx, x0, x1);
        });

    auto r = static_b_acc(   // .
        int_v<1>, int_v<10>, // .
        int_v<2>, int_v<10>, // .
        int_v<3>, int_v<10>, // .
        int_v<4>, int_v<10>);

    using r_type = decltype(r());

    static_assert(std::get<0>(r()) == int_v<1 + 2 + 3 + 4>);
    static_assert(std::get<1>(r()) == int_v<10 + 10 + 10 + 10>);
}

int main()
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
