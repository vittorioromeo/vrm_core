#include "../../utils/test_utils.hpp"
#include <vrm/core/literals.hpp>

TEST_MAIN()
{
    using namespace vrm::core::literals;

    SA_TYPE((0_c), (vrm::core::llong_<0>));
    SA_TYPE((1_c), (vrm::core::llong_<1>));
    SA_TYPE((2_c), (vrm::core::llong_<2>));
    SA_TYPE((3_c), (vrm::core::llong_<3>));
    SA_TYPE((4_c), (vrm::core::llong_<4>));

    return 0;
}
