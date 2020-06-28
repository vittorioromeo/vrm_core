#include "../../utils/test_utils.hpp"
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits/qualifiers.hpp>

TEST_MAIN()
{
    static_assert(std::is_same<                            // .
        vrm::core::copy_const_qualifier<int, const float>, // .
        const int>{});

    static_assert(std::is_same<                                  // .
        vrm::core::copy_volatile_qualifier<int, volatile float>, // .
        volatile int>{});

    static_assert(std::is_same<                                   // .
        vrm::core::copy_cv_qualifiers<int, const volatile float>, // .
        const volatile int>{});

    return 0;
}
