#include "../../../utils/test_res_utils.hpp"
#include <vrm/core/experimental/handle2.hpp>

using namespace vrm::core;

template <typename T>
auto t0(T m)
{
    {
        auto h0 = m.create(10);
        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT_OP(m.access(h0), ==, 10);

        m.destroy(h0);

        TEST_ASSERT(!m.valid(h0));
    }

    {
        auto h0 = m.create(15);
        auto h1 = h0;
        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT_OP(m.access(h0), ==, 15);
        TEST_ASSERT_OP(m.access(h1), ==, 15);

        m.destroy(h0);

        TEST_ASSERT(!m.valid(h0));
        TEST_ASSERT(!m.valid(h1));
    }

    {
        auto h0 = m.create(0);
        auto h1 = m.create(1);
        auto h2 = m.create(2);
        auto h3 = m.create(3);

        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT(m.valid(h2));
        TEST_ASSERT(m.valid(h3));

        TEST_ASSERT_OP(m.access(h0), ==, 0);
        TEST_ASSERT_OP(m.access(h1), ==, 1);
        TEST_ASSERT_OP(m.access(h2), ==, 2);
        TEST_ASSERT_OP(m.access(h3), ==, 3);

        m.destroy(h2);

        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT(!m.valid(h2));
        TEST_ASSERT(m.valid(h3));

        TEST_ASSERT_OP(m.access(h0), ==, 0);
        TEST_ASSERT_OP(m.access(h1), ==, 1);
        // x
        TEST_ASSERT_OP(m.access(h3), ==, 3);
    }

    {
        auto h0 = m.create(0);
        auto h1 = m.create(1);
        auto h2 = m.create(2);
        auto h3 = m.create(3);

        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT(m.valid(h2));
        TEST_ASSERT(m.valid(h3));

        TEST_ASSERT_OP(m.access(h0), ==, 0);
        TEST_ASSERT_OP(m.access(h1), ==, 1);
        TEST_ASSERT_OP(m.access(h2), ==, 2);
        TEST_ASSERT_OP(m.access(h3), ==, 3);

        m.destroy(h2);
        m.destroy(h1);

        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(!m.valid(h1));
        TEST_ASSERT(!m.valid(h2));
        TEST_ASSERT(m.valid(h3));

        TEST_ASSERT_OP(m.access(h0), ==, 0);
        // x
        // x
        TEST_ASSERT_OP(m.access(h3), ==, 3);
    }

    {
        auto h0 = m.create(0);
        auto h1 = m.create(1);
        auto h2 = m.create(2);
        auto h3 = m.create(3);

        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT(m.valid(h2));
        TEST_ASSERT(m.valid(h3));

        TEST_ASSERT_OP(m.access(h0), ==, 0);
        TEST_ASSERT_OP(m.access(h1), ==, 1);
        TEST_ASSERT_OP(m.access(h2), ==, 2);
        TEST_ASSERT_OP(m.access(h3), ==, 3);

        m.destroy(h1);
        m.destroy(h2);

        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(!m.valid(h1));
        TEST_ASSERT(!m.valid(h2));
        TEST_ASSERT(m.valid(h3));

        TEST_ASSERT_OP(m.access(h0), ==, 0);
        // x
        // x
        TEST_ASSERT_OP(m.access(h3), ==, 3);
    }

    {
        auto h0 = m.create(0);
        auto h1 = m.create(1);
        auto h2 = m.create(2);
        auto h3 = m.create(3);

        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT(m.valid(h2));
        TEST_ASSERT(m.valid(h3));

        TEST_ASSERT_OP(m.access(h0), ==, 0);
        TEST_ASSERT_OP(m.access(h1), ==, 1);
        TEST_ASSERT_OP(m.access(h2), ==, 2);
        TEST_ASSERT_OP(m.access(h3), ==, 3);

        m.destroy(h0);
        m.destroy(h3);

        TEST_ASSERT(!m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT(m.valid(h2));
        TEST_ASSERT(!m.valid(h3));

        // x
        TEST_ASSERT_OP(m.access(h1), ==, 1);
        TEST_ASSERT_OP(m.access(h2), ==, 2);
        // x
    }

    {
        auto h0 = m.create(0);
        auto h1 = m.create(10);
        auto h2 = m.create(20);
        auto h3 = m.create(30);
        auto h4 = m.create(40);
        auto h5 = m.create(50);

        TEST_ASSERT(m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT(m.valid(h2));
        TEST_ASSERT(m.valid(h3));
        TEST_ASSERT(m.valid(h4));
        TEST_ASSERT(m.valid(h5));

        TEST_ASSERT_OP(m.access(h0), ==, 0);
        TEST_ASSERT_OP(m.access(h1), ==, 10);
        TEST_ASSERT_OP(m.access(h2), ==, 20);
        TEST_ASSERT_OP(m.access(h3), ==, 30);
        TEST_ASSERT_OP(m.access(h4), ==, 40);
        TEST_ASSERT_OP(m.access(h5), ==, 50);

        m.destroy(h0);
        m.destroy(h2);
        m.destroy(h4);

        TEST_ASSERT(!m.valid(h0));
        TEST_ASSERT(m.valid(h1));
        TEST_ASSERT(!m.valid(h2));
        TEST_ASSERT(m.valid(h3));
        TEST_ASSERT(!m.valid(h4));
        TEST_ASSERT(m.valid(h5));

        // xTEST_ASSERT_OP(m.access(h0), ==, 0);
        TEST_ASSERT_OP(m.access(h1), ==, 10);
        // xTEST_ASSERT_OP(m.access(h2), ==, 20);
        TEST_ASSERT_OP(m.access(h3), ==, 30);
        // xTEST_ASSERT_OP(m.access(h4), ==, 40);
        TEST_ASSERT_OP(m.access(h5), ==, 50);
    }

    return m;
}

TEST_MAIN()
{
    using setts = handle2::settings<sz_t, unsigned int, int>;
    {
        handle2::container::owning_packed_array<setts, 40> m0;
        auto m1 = t0(std::move(m0));
        auto m2 = t0(std::move(m1));
        auto m3 = t0(std::move(m2));
        m3.clear();
        auto m4 = t0(std::move(m3));
        auto m5 = t0(std::move(m4));
        t0(std::move(m5));
    }

    {
        handle2::container::owning_packed_array<setts, 40> m0;
        auto m1 = t0(m0);
        auto m2 = t0(m1);
        auto m3 = t0(m2);
        m3.clear();
        auto m4 = t0(m3);
        auto m5 = t0(m4);
        t0(m5);
    }
}
