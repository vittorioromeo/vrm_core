#include "../../utils/test_utils.hpp"
#include <vrm/core/type_traits/copy_if_rvalue.hpp>
#include <vrm/core/assert.hpp>

using namespace vrm::core;

// More information:
// http://stackoverflow.com/questions/36892827

struct X
{
    X()
    {
    }

    X(const X&)
    {
    }

    X(const volatile X&)
    {
    }

    X(X&&)
    {
    }

    X(volatile X&&)
    {
    }

    X(const volatile X&&)
    {
    }
};

SA_TYPE((copy_if_rvalue(1)), (int));
SA_TYPE((copy_if_rvalue(1.f)), (float));
SA_TYPE((copy_if_rvalue(1.0)), (double));

void x()
{
    int lv = 1;
    const int clv = 1;
    volatile int vlv = 1;
    const volatile int cvlv = 1;

    SA_TYPE((copy_if_rvalue(1)), (int));
    SA_TYPE((copy_if_rvalue(lv)), (int&));
    SA_TYPE((copy_if_rvalue(clv)), (const int&));
    SA_TYPE((copy_if_rvalue(vlv)), (volatile int&));
    SA_TYPE((copy_if_rvalue(cvlv)), (volatile const int&));
}

template <typename T>
decltype(auto) id(T&& x)
{
    return FWD(x);
}

void TEST_CONST y()
{
    X v;
    const X cv;
    volatile X vv;
    const volatile X cvv;

    SA_TYPE((std::move(v)), (X && ));
    SA_SAME((decltype(v)), (X));
    SA_TYPE((id(std::move(v))), (X && ));
    SA_SAME((std::remove_reference_t<decltype(FWD(v))>), (X));
    SA_TYPE((copy_if_rvalue(std::move(v))), (X));

    SA_TYPE((std::move(cv)), (const X&&));
    SA_SAME((decltype(cv)), (const X));
    SA_TYPE((id(std::move(cv))), (const X&&));
    SA_SAME((std::remove_reference_t<decltype(FWD(cv))>), (const X));

    SA_SAME((decltype(id(std::move(cv)))), (const X&&));
    SA_SAME(
        (std::remove_reference_t < decltype(id(std::move(cv)))) >, (const X));
    SA_TYPE((copy_if_rvalue(std::move(cv))), (const X));


    SA_TYPE((std::move(vv)), (volatile X && ));
    SA_SAME((decltype(vv)), (volatile X));
    SA_TYPE((id(std::move(vv))), (volatile X && ));
    SA_SAME((std::remove_reference_t<decltype(FWD(vv))>), (volatile X));
    SA_TYPE((copy_if_rvalue(std::move(vv))), (volatile X));

    SA_TYPE((std::move(cvv)), (const volatile X&&));
    SA_SAME((decltype(cvv)), (const volatile X));
    SA_TYPE((id(std::move(cvv))), (const volatile X&&));
    SA_SAME((std::remove_reference_t<decltype(FWD(cvv))>), (const volatile X));
    SA_TYPE((copy_if_rvalue(std::move(cvv))), (const volatile X));
}

TEST_MAIN()
{
    x();
    y();
    return 0;
}
