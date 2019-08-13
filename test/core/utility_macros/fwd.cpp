#include "../../utils/test_utils.hpp"
#include <vrm/core/utility_macros/fwd.hpp>

template <typename... Ts>
void func(Ts&&... xs)
{
    (void)(VRM_CORE_FWD(xs), ...);
    (void)(FWD(xs), ...);
}

TEST_MAIN()
{
    func(VRM_CORE_FWD(0), VRM_CORE_FWD(1), VRM_CORE_FWD(2));
    func(FWD(0), FWD(1), FWD(2));
    return 0;
}
