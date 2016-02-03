#include "../../../utils/test_utils.hpp"
#include <vrm/core/config/detection.hpp>

TEST_MAIN()
{
    using namespace vrm::core;

    auto current_compiler(detection::current_compiler());

    TEST_ASSERT(current_compiler == detection::compiler::clang ||
                current_compiler == detection::compiler::gcc);

    return 0;
}
