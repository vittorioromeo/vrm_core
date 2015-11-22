#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/enum.hpp>

enum class test_enum : int
{
    a = 10,
    b = 20
};

enum class uint_enum : unsigned int
{
    a = 0,
    b = 1
};

enum class int_enum : int
{
    a = -1,
    b = -2
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

    // Fires runtime assertion as intended:
    // (void) to_enum<uint_enum>(int_enum::a);

    (void) to_enum<int_enum>(uint_enum::a);

    (void) to_enum<uint_enum>(0);
    (void) to_enum<uint_enum>(1);

    // Fires runtime assertion as intended:
    // (void) to_enum<uint_enum>(-1);

    return 0;
}
