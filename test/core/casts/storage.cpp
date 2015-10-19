#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/storage.hpp>
#include <utility>

int main()
{
    using namespace vrm::core;
    using st = std::aligned_storage_t<sizeof(float), alignof(float)>;

    st s;
    new(&s) float(100.f);

    TEST_ASSERT(from_storage<float>(s) == 100.f);
    TEST_ASSERT(*(from_storage<float>(&s)) == 100.f);

    const auto& cs(s);

    TEST_ASSERT(from_storage<float>(cs) == 100.f);
    TEST_ASSERT(*(from_storage<float>(&cs)) == 100.f);

    return 0;
}