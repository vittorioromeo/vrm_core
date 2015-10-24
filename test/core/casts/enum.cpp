#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/enum.hpp>

enum class test_enum : int
{
    a = 10,
    b = 20
};

int main()
{
    using namespace vrm::core;

    TEST_ASSERT(from_enum(test_enum::a) == 10);
    TEST_ASSERT(from_enum(test_enum::b) == 20);

    TEST_ASSERT(to_enum<test_enum>(10) == test_enum::a);
    TEST_ASSERT(to_enum<test_enum>(20) == test_enum::b);

    TEST_ASSERT(from_enum<long>(test_enum::a) == 10);
    TEST_ASSERT(from_enum<long>(test_enum::b) == 20);

    TEST_ASSERT(from_enum<float>(test_enum::a) == 10.f);
    TEST_ASSERT(from_enum<float>(test_enum::b) == 20.f);

    return 0;
}