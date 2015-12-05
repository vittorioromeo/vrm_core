#include "../../utils/test_utils.hpp"
#include <vrm/core/for_args/for_args_complete.hpp>

using namespace vrm::core;

template <typename T0, typename T1>
struct sum_int_c
{
    using type = int_<T0{} + T1{}>;
};

template <typename T0, typename T1>
using sum_int_c_t = typename sum_int_c<T0, T1>::type;

void test_magic()
{

    // TODO: major refactoring/abstraction required

    // The following call computes the sum of the int_v values at compile time,
    // by recursively keeping track of the last returned type from the for args
    // iterations.

    // It is necessary to wrap the return type in a specific wrapper to allow
    // usage of void and it is also currently not compatibl with
    // continue/break/skip constructs.

    // TODO: major work required

    auto x = static_for_args<1>([&](auto metadata, auto x_wrapper)
        {
            using metadata_type = decltype(metadata);
            using lrt = typename metadata_type::last_return_type;

            constexpr auto x(decltype(x_wrapper){});
            // std::cout << typeid(lrt).name() << "\n";

            return static_if(bool_v<std::is_same<void, lrt>{}>)
                .then([](auto y)
                    {
                        return y;
                    })
                .else_([](auto y)
                    {
                        return sum_int_c_t<lrt, decltype(y)>{};
                    })(x);

        })(int_v<1>, int_v<2>, int_v<3>, int_v<4>);

    static_assert(std::is_same<decltype(x)::type, int_<1 + 2 + 3 + 4>>{}, "");
}

void test_continue()
{
    sz_t acc = 0;


    static_for_args<1>([&](auto, auto x_wrapper)
        {
            constexpr auto x(decltype(x_wrapper){});
            return static_if(bool_v<(x >= 10)>)
                .then([&](auto y)
                    {
                        return static_if(bool_v<(y == 99)>)
                            .then([](auto)
                                {
                                    return break_t{};
                                })
                            .else_([](auto)
                                {
                                    return continue_t{};
                                })(y);
                    })
                .else_([&](auto y)
                    {
                        acc += y;
                        return y;
                    })(x);
        })(sz_t_v<1>, sz_t_v<10>, sz_t_v<1>, sz_t_v<10>, sz_t_v<99>, sz_t_v<1>);

    TEST_ASSERT_OP(acc, ==, 2);
}

int main()
{
    test_magic();
    // TODO:
    return 0;

    static_for_args([](auto data, auto x_wrapper)
        {
            constexpr auto x(decltype(x_wrapper){});
            std::cout << x << "\n";

            return static_if(bool_v<(x == 2)>)
                .then([](auto y)
                    {
                        return break_t{};
                    })
                .else_([](auto y)
                    {
                        return skip_t<1>{};
                    })(x);

        })(sz_t_<0>{}, sz_t_<1>{}, sz_t_<2>{}, sz_t_<3>{}, sz_t_<4>{},
        sz_t_<5>{}, sz_t_<6>{});

    return 0;

    static_for_args([](auto data, auto&& x)
        {
            return static_if(
                       bool_v<std::is_same<std::remove_reference_t<decltype(x)>,
                           float>{}>)
                .then([](auto&& v)
                    {
                        std::cout << "skip " << decltype(data)::iteration
                                  << "\n";
                        // return continue_t{};
                        // return break_t{};
                    })
                .else_([](auto&& v)
                    {
                        std::cout << decltype(data)::iteration << ": " << v
                                  << "\n";
                    })(x);

        })(1, "hello", 'a', 3, 4.f, 2, 1, 'b');

    std::cout << "\n\n";

    static_for_args<2>([](auto data, auto&& x, auto&&)
        {
            return static_if(
                       bool_v<std::is_same<std::remove_reference_t<decltype(x)>,
                           float>{}>)
                .then([](auto&& v)
                    {
                        std::cout << "skip " << decltype(data)::iteration
                                  << "\n";
                        // return continue_t{};
                        // return break_t{};
                    })
                .else_([](auto&& v)
                    {
                        std::cout << decltype(data)::iteration << ": " << v
                                  << "\n";
                    })(x);

        })(1, "hello", 'a', 3, 4.f, 2, 1, 'b');


    test_continue();
}
