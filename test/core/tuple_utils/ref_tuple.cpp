#include "../../utils/test_utils.hpp"
#include <vrm/core/config.hpp>
#include <vrm/core/tuple_utils/ref_tuple.hpp>

int main()
{
    auto lv = 10;
    const auto clv = 15;

    auto t = vrm::core::make_ref_tuple(lv, clv, 20, std::move(lv));

    SA_SAME((std::tuple_element_t<0, decltype(t)>), (int&));
    SA_SAME((std::tuple_element_t<1, decltype(t)>), (const int&));
    SA_SAME((std::tuple_element_t<2, decltype(t)>), (int));
    SA_SAME((std::tuple_element_t<3, decltype(t)>), (int));

    SA_TYPE((std::get<0>(t)), (int&));
    SA_TYPE((std::get<1>(t)), (const int&));
    SA_TYPE((std::get<2>(t)), (int&));
    SA_TYPE((std::get<3>(t)), (int&));

    return 0;
}