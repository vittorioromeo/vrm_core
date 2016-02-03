#include "../../utils/test_utils.hpp"
#include <cstddef>
#include <vrm/core/config.hpp>
#include <vrm/core/is_valid.hpp>
#include <vrm/core/for_args.hpp>
#include <vrm/core/static_if.hpp>

using namespace vrm::core;

struct banana
{
    int x;
    void peel() {}
    void eat_banana() {}
};

struct apple
{
    int y;
    void peel() {}
    void eat_apple() {}
};

struct chestnut
{
    int z;
    void peel() {}
};

auto has_peel(is_valid([](auto&& x) -> decltype(x.peel())
    {
    }));

auto has_eat_banana(is_valid([](auto&& x) -> decltype(x.eat_banana())
    {
    }));

auto has_eat_apple(is_valid([](auto&& x) -> decltype(x.eat_apple())
    {
    }));

auto has_x(is_valid([](auto&& x) -> decltype(x.x)
    {
    }));

auto has_y(is_valid([](auto&& x) -> decltype(x.y)
    {
    }));

auto has_z(is_valid([](auto&& x) -> decltype(x.z)
    {
    }));


template <typename T>
struct type_
{
    using type = T;
};

TEST_MAIN()
{
    static_assert(has_peel(banana{}), "");
    static_assert(has_eat_banana(banana{}), "");
    static_assert(!has_eat_apple(banana{}), "");

    static_assert(has_peel(apple{}), "");
    static_assert(!has_eat_banana(apple{}), "");
    static_assert(has_eat_apple(apple{}), "");

    static_assert(has_peel(chestnut{}), "");
    static_assert(!has_eat_banana(chestnut{}), "");
    static_assert(!has_eat_apple(chestnut{}), "");

    static_assert(has_x(banana{}), "");
    static_assert(!has_y(banana{}), "");
    static_assert(!has_z(banana{}), "");

    static_assert(!has_x(apple{}), "");
    static_assert(has_y(apple{}), "");
    static_assert(!has_z(apple{}), "");

    static_assert(!has_x(chestnut{}), "");
    static_assert(!has_y(chestnut{}), "");
    static_assert(has_z(chestnut{}), "");

    for_args(
        [](auto t)
        {
            using real_t = typename decltype(t)::type;

            static_if(has_peel(real_t{}))
                .then([](auto&& x)
                    {
                        x.peel();
                    })(real_t{});

            static_if(has_eat_banana(real_t{}))
                .then([](auto&& x)
                    {
                        x.eat_banana();
                    })(real_t{});

            static_if(has_eat_apple(real_t{}))
                .then([](auto&& x)
                    {
                        x.eat_apple();
                    })(real_t{});
        },
        type_<banana>{}, type_<apple>{}, type_<chestnut>{});

    return 0;
}
