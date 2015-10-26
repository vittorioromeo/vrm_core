#include "../../utils/test_utils.hpp"
#include <vrm/core/multi_vector.hpp>

volatile int cc = 0;
volatile int dd = 0;
volatile int copies = 0;

struct item
{
    int l;
    item() { ++cc; }

    item(const item&) { ++copies; }
    item(item&&) = delete;

    item& operator=(const item&)
    {
        ++copies;
        return *this;
    }

    ~item() { ++dd; }
};


int main()
{
    using namespace vrm::core;

    {
        {
            cc = dd = copies = 0;

            using mb_type = multi_resizable_buffer<resizable_buffer<int>,
                resizable_buffer<float>, resizable_buffer<item>>;

            using mv_type = impl::multi_vector<mb_type>;

            mv_type mv;

            TEST_ASSERT_OP(mv.capacity(), ==, mv_type::initial_capacity);
            TEST_ASSERT_OP(mv.size(), ==, 0);
            TEST_ASSERT_OP(cc, ==, 0);
            TEST_ASSERT_OP(copies, ==, 0);
            TEST_ASSERT_OP(dd, ==, 0);

            static_assert(
                std::is_same<decltype(mv[0]), mv_type::value_reference_tuple>{},
                "");

            static_assert(
                std::is_same<decltype(static_cast<const mv_type&>(mv)[0]),
                    mv_type::const_value_reference_tuple>{},
                "");

            mv.reserve(100);

            TEST_ASSERT_OP(mv.capacity(), ==, 100);
            TEST_ASSERT_OP(mv.size(), ==, 0);
            TEST_ASSERT_OP(cc, ==, 0);
            TEST_ASSERT_OP(copies, ==, 0);
            TEST_ASSERT_OP(dd, ==, 0);

            mv.resize(50);

            TEST_ASSERT_OP(mv.capacity(), ==, 100);
            TEST_ASSERT_OP(mv.size(), ==, 50);
            TEST_ASSERT_OP(cc, ==, 50);
            TEST_ASSERT_OP(copies, ==, 0);
            TEST_ASSERT_OP(dd, ==, 0);

            mv.resize(100);

            TEST_ASSERT_OP(mv.capacity(), ==, 100);
            TEST_ASSERT_OP(mv.size(), ==, 100);
            TEST_ASSERT_OP(cc, ==, 100);
            TEST_ASSERT_OP(copies, ==, 0);
            TEST_ASSERT_OP(dd, ==, 0);

            mv.resize(150);

            TEST_ASSERT_OP(mv.capacity(), >, 100);
            TEST_ASSERT_OP(mv.size(), ==, 150);
            TEST_ASSERT_OP(cc, ==, 150);
            TEST_ASSERT_OP(copies, ==, 100);
            TEST_ASSERT_OP(dd, ==, 100);
        }

        TEST_ASSERT_OP(cc, ==, 150);
        TEST_ASSERT_OP(copies, ==, 100);
        TEST_ASSERT_OP(dd, ==, 250);
    }



    return 0;
}