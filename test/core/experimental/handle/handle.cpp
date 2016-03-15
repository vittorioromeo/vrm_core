#include "../../../utils/test_res_utils.hpp"
#include <vrm/core/experimental/handle.hpp>

using namespace vrm::core;

template <typename TMgr>
void t()
{
    TMgr m;

    {
        auto h0 = m.create(10);
        TEST_ASSERT(m.valid_handle(h0));
        TEST_ASSERT_OP(m.access(h0), ==, 10);

        m.destroy(h0, [](auto)
            {
            });

        TEST_ASSERT(!m.valid_handle(h0));
    }

    {
        auto h0 = m.create(15);
        auto h1 = h0;
        TEST_ASSERT(m.valid_handle(h0));
        TEST_ASSERT(m.valid_handle(h1));
        TEST_ASSERT_OP(m.access(h0), ==, 15);
        TEST_ASSERT_OP(m.access(h1), ==, 15);

        m.destroy(h0, [](auto)
            {
            });

        TEST_ASSERT(!m.valid_handle(h0));
        TEST_ASSERT(!m.valid_handle(h1));
    }
}

void t2()
{
    std::vector<sz_t> entities;
    entities.resize(5);
    entities[0] = 2;
    entities[1] = 4;
    entities[2] = 6;
    entities[3] = 8;
    entities[4] = 10;

    std::vector<int> counters;
    counters.resize(5);

    using my_metadata_ref = sz_t;

    auto my_getter_target = [&](my_metadata_ref mr) -> decltype(auto)
    {
        return entities[mr];
    };

    auto my_getter_counter = [&](my_metadata_ref mr) -> decltype(auto)
    {
        return counters[mr];
    };

    handle::custom_manager<sz_t, int, my_metadata_ref,
        std::decay_t<decltype(my_getter_target)>,
        std::decay_t<decltype(my_getter_counter)>> m(my_getter_target,
        my_getter_counter);

    {
        auto h0 = m.create(2);
        TEST_ASSERT(m.valid_handle(h0));
        TEST_ASSERT_OP(m.access(h0), ==, 2);
        TEST_ASSERT_OP(entities[m.access(h0)], ==, 6);

        m.destroy(h0, [](auto)
            {
            });

        TEST_ASSERT(!m.valid_handle(h0));
    }

    {
        auto hx = m.create(4);
        auto h0 = m.create(3);
        auto h1 = h0;
        TEST_ASSERT(m.valid_handle(hx));
        TEST_ASSERT(m.valid_handle(h0));
        TEST_ASSERT(m.valid_handle(h1));
        TEST_ASSERT_OP(m.access(hx), ==, 4);
        TEST_ASSERT_OP(m.access(h0), ==, 3);
        TEST_ASSERT_OP(entities[m.access(hx)], ==, 10);
        TEST_ASSERT_OP(entities[m.access(h0)], ==, 8);
        TEST_ASSERT_OP(m.access(h1), ==, 3);
        TEST_ASSERT_OP(entities[m.access(h1)], ==, 8);

        m.destroy(h0, [](auto)
            {
            });

        TEST_ASSERT(!m.valid_handle(h0));
        TEST_ASSERT(!m.valid_handle(h1));

        TEST_ASSERT(m.valid_handle(hx));
        TEST_ASSERT_OP(m.access(hx), ==, 4);
        TEST_ASSERT_OP(entities[m.access(hx)], ==, 10);
    }
}

TEST_MAIN()
{
    using target = unsigned int;
    using counter = int;

    t<handle::array_manager<target, counter, 100>>();
    t<handle::vector_manager<target, counter>>();
    t2();
}
