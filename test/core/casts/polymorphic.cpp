#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/polymorphic.hpp>

struct base
{
    virtual ~base() {}
    virtual int x() const { return 0; }
};

struct derived : base
{
    int x() const override { return 1; }
};

int main()
{
    using namespace vrm::core;

    derived d0;

    base* bptr(&d0);
    base& bref(d0);
    const base* cbptr(&d0);
    const base& cbref(d0);

    TEST_ASSERT(to_derived<derived>(bptr)->x() == 1);
    TEST_ASSERT(to_derived<derived>(bref).x() == 1);

    TEST_ASSERT(to_derived<derived>(cbptr)->x() == 1);
    TEST_ASSERT(to_derived<derived>(cbref).x() == 1);

    return 0;
}