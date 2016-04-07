#include "../../utils/test_utils.hpp"
#include <vrm/core/type_traits/referenceness.hpp>
#include <vrm/core/assert.hpp>

using namespace vrm::core;

SA_SAME((copy_referenceness<float, int>), (float));
SA_SAME((copy_referenceness<float, int&>), (float&));
SA_SAME((copy_referenceness<float, int&&>), (float&&));

SA_SAME((copy_referenceness<float&, int>), (float));
SA_SAME((copy_referenceness<float&, int&>), (float&));
SA_SAME((copy_referenceness<float&, int&&>), (float&&));

SA_SAME((copy_referenceness<float&&, int>), (float));
SA_SAME((copy_referenceness<float&&, int&>), (float&));
SA_SAME((copy_referenceness<float&&, int&&>), (float&&));

// `copy_referenceness` maintains existing qualifiers.

SA_SAME((copy_referenceness<float, const int>), (float));
SA_SAME((copy_referenceness<float, const int&>), (float&));
SA_SAME((copy_referenceness<float, const int&&>), (float&&));

SA_SAME((copy_referenceness<float&, const int>), (float));
SA_SAME((copy_referenceness<float&, const int&>), (float&));
SA_SAME((copy_referenceness<float&, const int&&>), (float&&));

SA_SAME((copy_referenceness<float&&, const int>), (float));
SA_SAME((copy_referenceness<float&&, const int&>), (float&));
SA_SAME((copy_referenceness<float&&, const int&&>), (float&&));

SA_SAME((copy_referenceness<const float, int>), (const float));
SA_SAME((copy_referenceness<const float, int&>), (const float&));
SA_SAME((copy_referenceness<const float, int&&>), (const float&&));

SA_SAME((copy_referenceness<const float&, int>), (const float));
SA_SAME((copy_referenceness<const float&, int&>), (const float&));
SA_SAME((copy_referenceness<const float&, int&&>), (const float&&));

SA_SAME((copy_referenceness<const float&&, int>), (const float));
SA_SAME((copy_referenceness<const float&&, int&>), (const float&));
SA_SAME((copy_referenceness<const float&&, int&&>), (const float&&));

TEST_MAIN()
{
    return 0;
}
