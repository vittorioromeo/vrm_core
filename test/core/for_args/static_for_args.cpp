#include "../../utils/test_utils.hpp"
#include <vrm/core/for_args/for_args_complete.hpp>

int main()
{
    using namespace vrm::core;



    static_for_args([](auto data, auto x_wrapper)
        {
            constexpr auto x(decltype(x_wrapper){});
            std::cout << x << "\n";

            return static_if(bool_<(x == 2)>{})
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
                       bool_<std::is_same<std::remove_reference_t<decltype(x)>,
                           float>{}>{})
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
                       bool_<std::is_same<std::remove_reference_t<decltype(x)>,
                           float>{}>{})
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
}
