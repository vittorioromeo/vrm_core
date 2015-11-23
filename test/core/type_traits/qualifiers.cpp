#include "../../utils/test_utils.hpp"
#include <vrm/core/type_traits/qualifiers.hpp>
#include <vrm/core/assert.hpp>

int main()
{
    VRM_CORE_STATIC_ASSERT_NM(std::is_same<                // .
        vrm::core::copy_const_qualifier<int, const float>, // .
        const int>{});

    VRM_CORE_STATIC_ASSERT_NM(std::is_same<                      // .
        vrm::core::copy_volatile_qualifier<int, volatile float>, // .
        volatile int>{});

    VRM_CORE_STATIC_ASSERT_NM(std::is_same<                       // .
        vrm::core::copy_cv_qualifiers<int, const volatile float>, // .
        const volatile int>{});

    return 0;
}
