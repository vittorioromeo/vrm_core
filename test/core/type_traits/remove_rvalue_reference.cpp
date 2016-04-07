#include "../../utils/test_utils.hpp"
#include <vrm/core/type_traits/remove_rvalue_reference.hpp>
#include <vrm/core/assert.hpp>

using namespace vrm::core;

SA_SAME((remove_rvalue_reference_t<int>), (int));
SA_SAME((remove_rvalue_reference_t<int&>), (int&));
SA_SAME((remove_rvalue_reference_t<int&&>), (int));

SA_SAME((remove_rvalue_reference_t<const int>), (const int));
SA_SAME((remove_rvalue_reference_t<const int&>), (const int&));
SA_SAME((remove_rvalue_reference_t<const int&&>), (const int));

SA_SAME((remove_rvalue_reference_t<volatile int>), (volatile int));
SA_SAME((remove_rvalue_reference_t<volatile int&>), (volatile int&));
SA_SAME((remove_rvalue_reference_t<volatile int&&>), (volatile int));

SA_SAME((remove_rvalue_reference_t<const volatile int>), (const volatile int));
SA_SAME(
    (remove_rvalue_reference_t<const volatile int&>), (const volatile int&));
SA_SAME(
    (remove_rvalue_reference_t<const volatile int&&>), (const volatile int));

TEST_MAIN()
{
    return 0;
}
