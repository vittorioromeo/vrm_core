#include "../../utils/test_utils.hpp"
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits/is_specialization_of.hpp>

using namespace vrm::core;

template <typename>
struct S1
{
};

template <typename, typename>
struct S2
{
};

template <typename...>
struct SV
{
};

template <typename = int>
struct SD1
{
};

static_assert(is_specialization_of_t<S1<int>, S1>{} );
static_assert(!is_specialization_of_t<S1<int>, S2>{} );
static_assert(!is_specialization_of_t<S1<int>, SV>{} );

static_assert(is_specialization_of_t<S2<int, float>, S2>{} );
static_assert(!is_specialization_of_t<SV<int, float>, S2>{} );

static_assert(is_specialization_of_t<SV<int, float, char>, SV>{} );
static_assert(is_specialization_of_t<SV<>, SV>{} );

static_assert(is_specialization_of_t<SD1<>, SD1>{} );
static_assert(is_specialization_of_t<SD1<int>, SD1>{} );
static_assert(is_specialization_of_t<SD1<float>, SD1>{} );

static_assert(is_specialization_of_v<S1<int>, S1> );
static_assert(!is_specialization_of_v<S1<int>, S2> );
static_assert(!is_specialization_of_v<S1<int>, SV> );

static_assert(is_specialization_of_v<S2<int, float>, S2> );
static_assert(!is_specialization_of_v<SV<int, float>, S2> );

static_assert(is_specialization_of_v<SV<int, float, char>, SV> );
static_assert(is_specialization_of_v<SV<>, SV> );

static_assert(is_specialization_of_v<SD1<>, SD1> );
static_assert(is_specialization_of_v<SD1<int>, SD1> );
static_assert(is_specialization_of_v<SD1<float>, SD1> );

TEST_MAIN()
{
    return 0;
}
