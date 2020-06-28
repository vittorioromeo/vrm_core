#include "../../../utils/test_res_utils.hpp"
#include <vector>
#include <vrm/core/experimental/handle2/context.hpp>

using namespace vrm::core;

using ex_set = handle2::settings<sz_t, float, int>;
struct example : handle2::context<ex_set, example>
{
    std::vector<float> items;
    std::vector<int> counters;

    example()
    {
        items.resize(5);
        counters.resize(5);

        items[0] = 5;
        items[1] = 10;
        items[2] = 15;
        items[3] = 20;
        items[4] = 25;
    }

    auto& target(sz_t x)
    {
        return items[x];
    }
    [[nodiscard]] const auto& target(sz_t x) const
    {
        return items[x];
    }

    auto& counter(sz_t x)
    {
        return counters[x];
    }
    [[nodiscard]] const auto& counter(sz_t x) const
    {
        return counters[x];
    }

    void invalidate_x(sz_t x)
    {
        this->invalidate(x);
    }

    auto& access(const handle_type& h)
    {
        VRM_CORE_ASSERT(valid(h));
        return target(data(h));
    }
    [[nodiscard]] const auto& access(const handle_type& h) const
    {
        VRM_CORE_ASSERT(valid(h));
        return target(data(h));
    }
};

TEST_MAIN()
{
    auto context = example{};

    for(auto i = 0; i < 5; ++i)
    {
        auto h0 = context.create_handle_from_data(0);
        TEST_ASSERT(context.valid(h0));
        TEST_ASSERT_OP(context.access(h0), ==, 5);

        context.invalidate_x(0);
        TEST_ASSERT(!context.valid(h0));
    }
}
