#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/polymorphic.hpp>

struct base
{
    virtual ~base()
    {
    }
    [[nodiscard]] virtual int x() const
    {
        return 0;
    }
};

struct derived final : base
{
    [[nodiscard]] int x() const override
    {
        return 1;
    }
};

using namespace vrm::core;

SA_TYPE((to_derived<derived>(base{})), (derived &&));

TEST_MAIN()
{
    derived d0;

    SA_TYPE((to_derived<derived>(d0)), (derived&));
    SA_TYPE((to_base<base>(d0)), (base&));

    SA_TYPE((to_derived<derived>(std::move(d0))), (derived &&));
    SA_TYPE((to_base<base>(std::move(d0))), (base &&));

    base* bptr(&d0);
    base& bref(d0);
    const base* cbptr(&d0);
    const base& cbref(d0);

    TEST_ASSERT(to_derived<derived>(bptr)->x() == 1);
    TEST_ASSERT(to_derived<derived>(bref).x() == 1);

    TEST_ASSERT(to_derived<derived>(cbptr)->x() == 1);
    TEST_ASSERT(to_derived<derived>(cbref).x() == 1);

    TEST_ASSERT(to_base<base>(d0).x() == 1);

    {
        auto d1 = new derived;

        TEST_ASSERT(d1->x() == 1);
        TEST_ASSERT(to_base<base>(d1)->x() == 1);
        TEST_ASSERT(to_base<base>(*d1).x() == 1);

        base* b1(d1);

        TEST_ASSERT(b1->x() == 1);
        TEST_ASSERT(to_derived<derived>(b1)->x() == 1);
        TEST_ASSERT(to_derived<derived>(*b1).x() == 1);

        delete d1;
    }

    return 0;
}
