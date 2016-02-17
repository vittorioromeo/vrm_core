#include "../../../utils/test_utils.hpp"
#include <vrm/core/config/detection.hpp>

#include <typeinfo>

TEST_MAIN()
{
    using namespace vrm::core;

    auto current_rtti(detection::rtti());
    (void)current_rtti;

#if defined(VRM_CORE_RTTI_ENABLED)
    (void)typeid(int);
#endif

    return 0;
}
