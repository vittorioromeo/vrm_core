#include "../../utils/test_utils.hpp"
#include <vrm/core/type_traits/void_t.hpp>
#include <vrm/core/assert.hpp>

using namespace vrm::core;

SA_SAME((void_t<>), (void));
SA_SAME((void_t<void>), (void));
SA_SAME((void_t<int>), (void));
SA_SAME((void_t<int, float>), (void));

TEST_MAIN()
{
    return 0;
}
