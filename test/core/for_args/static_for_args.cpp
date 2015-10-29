#include "../../utils/test_utils.hpp"
#include <vrm/core/for_args/for_args_complete.hpp>

int main()
{
    using namespace vrm::core;

    static_for_args([](auto&& x)
        {
            return static_if(
                       bool_<std::is_same<std::remove_reference_t<decltype(x)>,
                           float>{}>{})
                .then([](auto&& v)
                    {
                        return continue_t{};
                        // return break_t{};
                    })
                .else_([](auto&& v)
                    {
                        std::cout << v << "\n";
                    })(x);

        })(1, "hello", 'a', 3, 4.f, 2, 1, 'b');

    std::cout << "\n\n";

    static_for_args<2>([](auto&& x, auto&&)
        {
            return static_if(
                       bool_<std::is_same<std::remove_reference_t<decltype(x)>,
                           float>{}>{})
                .then([](auto&& v)
                    {
                        return continue_t{};
                        // return break_t{};
                    })
                .else_([](auto&& v)
                    {
                        std::cout << v << "\n";
                    })(x);

        })(1, "hello", 'a', 3, 4.f, 2, 1, 'b');
}
