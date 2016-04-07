#include "../../utils/test_utils.hpp"
#include <vrm/core/type_traits/forward_like.hpp>
#include <vrm/core/assert.hpp>

using namespace vrm::core;

int test_int;
float test_float;

SA_SAME((as_if_forwarded<float, int>), (float&&));
SA_SAME((as_if_forwarded<float, int&>), (float&));
SA_SAME((as_if_forwarded<float, int&&>), (float&&));

SA_SAME((as_if_forwarded<float&, int>), (float&&));
SA_SAME((as_if_forwarded<float&, int&>), (float&));
SA_SAME((as_if_forwarded<float&, int&&>), (float&&));

SA_SAME((as_if_forwarded<float&&, int>), (float&&));
SA_SAME((as_if_forwarded<float&&, int&>), (float&));
SA_SAME((as_if_forwarded<float&&, int&&>), (float&&));

// value(value), rvalue(value), value(rvalue), rvalue(rvalue)
SA_TYPE((std::forward<int>(int{})), (int&&));
SA_TYPE((std::forward<int&&>(int{})), (int&&));
SA_TYPE((std::forward<int>((int&&)(1))), (int&&));
SA_TYPE((std::forward<int&&>((int&&)(1))), (int&&));
// .
SA_TYPE((forward_like<int>(float{})), (float&&));
SA_TYPE((forward_like<int&&>(float{})), (float&&));
SA_TYPE((forward_like<int>((float&&)(1))), (float&&));
SA_TYPE((forward_like<int&&>((float&&)(1))), (float&&));

// lvalue(value), lvalue(lvalue), lvalue(rvalue)
// will static assert: SA_TYPE((std::forward<int&>(int{})), (int&));
SA_TYPE((std::forward<int&>(test_int)), (int&));
// will static assert: SA_TYPE((std::forward<int&>((int&&)(1))), (int&));
// .
// will static assert: SA_TYPE((forward_like<int&>(float{})), (float&));
SA_TYPE((forward_like<int&>(test_float)), (float&));
// will static assert: SA_TYPE((forward_like<int&>((float&&)(1))), (float&));

// value(lvalue), rvalue(lvalue)
SA_TYPE((std::forward<int>(test_int)), (int&&));
SA_TYPE((std::forward<int&&>(test_int)), (int&&));
// .
SA_TYPE((forward_like<int>(test_float)), (float&&));
SA_TYPE((forward_like<int&&>(test_float)), (float&&));

TEST_MAIN()
{
    return 0;
}
