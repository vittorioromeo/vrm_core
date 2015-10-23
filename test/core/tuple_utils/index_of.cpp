#include "../../utils/test_utils.hpp"
#include <vrm/core/detection.hpp>
#include <vrm/core/tuple_utils/index_of.hpp>

int main()
{
    std::tuple<int, float, char, int> t;

    using namespace vrm::core;

    TEST_ASSERT_OP(tuple_index_of<int>(t), ==, 0);
    TEST_ASSERT_OP(tuple_index_of<float>(t), ==, 1);
    TEST_ASSERT_OP(tuple_index_of<char>(t), ==, 2);

    TEST_ASSERT_OP((tuple_index_of<int, decltype(t)>()), ==, 0);
    TEST_ASSERT_OP((tuple_index_of<float, decltype(t)>()), ==, 1);
    TEST_ASSERT_OP((tuple_index_of<char, decltype(t)>()), ==, 2);

    return 0;
}