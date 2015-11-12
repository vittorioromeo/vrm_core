#include "../../utils/test_utils.hpp"
#include <vrm/core/config.hpp>
#include <typeinfo>
#include <vrm/core/tuple_utils/apply.hpp>

int main()
{
    using namespace vrm::core;

    std::tuple<int, char, float> t0{0, 'a', 0.f};
    std::tuple<int, char, float> t1{1, 'b', 1.f};
    std::tuple<int, char, float> t2{2, 'c', 2.f};

    using expected_tt_t = std::tuple<int&, int&, int&, char&, char&, char&,
        float&, float&, float&>;

    auto make_tuple_fwder = [](auto&&... xs) -> decltype(auto)
    {
        return std::make_tuple(FWD(xs)...);
    };

    auto forward_as_tuple_fwder = [](auto&&... xs) -> decltype(auto)
    {
        return std::forward_as_tuple(FWD(xs)...);
    };

    auto tt = tuple_transposer<decltype(t0), decltype(t1), decltype(t2)>{}.exec(
        forward_as_tuple_fwder, t0, t1, t2);

    using tt_t = std::decay_t<decltype(tt)>;

    std::cout << "T: " << typeid(tt_t).name() << std::endl;
    std::cout << "T: " << typeid(expected_tt_t).name() << std::endl;

    TEST_ASSERT_OP(std::get<0>(tt), ==, std::get<0>(t0));
    TEST_ASSERT_OP(std::get<1>(tt), ==, std::get<0>(t1));
    TEST_ASSERT_OP(std::get<2>(tt), ==, std::get<0>(t2));

    TEST_ASSERT_OP(std::get<3>(tt), ==, std::get<1>(t0));
    TEST_ASSERT_OP(std::get<4>(tt), ==, std::get<1>(t1));
    TEST_ASSERT_OP(std::get<5>(tt), ==, std::get<1>(t2));

    TEST_ASSERT_OP(std::get<6>(tt), ==, std::get<2>(t0));
    TEST_ASSERT_OP(std::get<7>(tt), ==, std::get<2>(t1));
    TEST_ASSERT_OP(std::get<8>(tt), ==, std::get<2>(t2));

    static_assert(std::is_same<tt_t, expected_tt_t>{}, "");

    return 0;
}

// TODO:
