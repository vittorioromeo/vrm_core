#include "./test_utils.hpp"
#include "./tracked_object.hpp"
#include <vrm/core/utility_macros/fwd.hpp>

TEST_MAIN()
{
    // clang-format off
    testing::check_operations([](auto& ctx)
    {
        auto a0 = ctx.anything("A");

    }).expect_that("A").ctors(1)
                       .no_copies()
                       .no_moves()
                       .dtors(1);

    testing::check_operations([](auto& ctx)
    {
        auto a0 = ctx.anything("A");
        auto a1 = a0;

    }).expect_that("A").ctors(1)
                       .copies(1)
                       .no_moves()
                       .dtors(2);

    testing::check_operations([](auto& ctx)
    {
        auto a0 = ctx.anything("A");
        auto a1 = a0;

        auto b0 = ctx.anything("B");
        auto b1 = std::move(b0);

    }).expect_that("A").ctors(1)
                       .copies(1)
                       .no_moves()
                       .dtors(2)
      .expect_that("B").ctors(1)
                       .no_copies()
                       .moves(1)
                       .dtors(2);
    // clang-format on


    return 0;
}
