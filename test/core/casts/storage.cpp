#include "../../utils/test_utils.hpp"
#include <utility>
#include <vrm/core/casts/storage.hpp>

TEST_MAIN()
{
    using namespace vrm::core;
    using st = std::aligned_storage_t<sizeof(float), alignof(float)>;

    st s;
    new(&s) float(100.f);

    TEST_ASSERT(storage_cast<float>(s) == 100.f);
    TEST_ASSERT(*(storage_cast<float>(&s)) == 100.f);

    const auto& cs(s);

    TEST_ASSERT(storage_cast<float>(cs) == 100.f);
    TEST_ASSERT(*(storage_cast<float>(&cs)) == 100.f);

    SA_TYPE((storage_cast<float>(s)), (float&));
    SA_TYPE((storage_cast<float>(std::move(s))), (float&&));

    return 0;
}
