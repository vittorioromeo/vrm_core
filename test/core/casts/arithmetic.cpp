#include "../../utils/test_utils.hpp"
#include <vrm/core/casts/arithmetic.hpp>

bool assert_fired{false};

#define FAKE_ASSERT(...)         \
    do                           \
    {                            \
        if(!(__VA_ARGS__))       \
        {                        \
            assert_fired = true; \
        }                        \
    } while(false)

void ensure_assert()
{
    assert(assert_fired);
    assert_fired = false;
}

template <typename TOut, typename TIn>
constexpr auto fake_to_num(const TIn& x) noexcept
{
    static_assert(std::is_arithmetic<TOut>{},
        "`TOut` output type must be an arithmetic type.");

    static_assert(std::is_arithmetic<TIn>{},
        "`TIn` input type must be an arithmetic type.");

    FAKE_ASSERT((!vrm::core::impl::will_overflow<TOut, TIn>(x)));

    return static_cast<TOut>(x);
}

template <typename TOut, typename TIn>
auto VRM_CORE_CONST_FN are_same_representation()
{
    return sizeof(std::decay_t<TOut>) == sizeof(std::decay_t<TIn>) &&
           vrm::core::same_signedness<std::decay_t<TOut>,
               std::decay_t<TIn>>{} &&
           std::is_integral<TOut>{} == std::is_integral<TIn>{};
}

template <typename TOut, typename TIn>
auto VRM_CORE_CONST_FN same_bytes_different_sign()
{
    return sizeof(std::decay_t<TOut>) == sizeof(std::decay_t<TIn>) &&
           !vrm::core::same_signedness<std::decay_t<TOut>, std::decay_t<TIn>>{};
}


template <typename TOut, typename TIn>
void test_val(const TIn& x, bool should_fire = false)
{
    assert_fired = false;
    if(are_same_representation<TOut, TIn>()) return;

    (void)fake_to_num<TOut>(x);

    if(should_fire)
    {
        ensure_assert();
    }
    else
    {
        assert(!assert_fired);
    }
}

template <typename TOut, typename TIn>
void test_type(bool should_fire = false)
{
    assert_fired = false;
    if(are_same_representation<TOut, TIn>()) return;
    if(same_bytes_different_sign<TOut, TIn>()) return;

    (void)fake_to_num<TOut>(std::numeric_limits<TIn>::lowest());
    (void)fake_to_num<TOut>(std::numeric_limits<TIn>::max());
    (void)fake_to_num<TOut>(static_cast<TIn>(0));
    (void)fake_to_num<TOut>(static_cast<TIn>(1));
    (void)fake_to_num<TOut>(static_cast<TIn>(2));

    if(should_fire)
    {
        ensure_assert();
    }
    else
    {
        assert(!assert_fired);
    }
}

void integral_tests()
{
    // Should not fire asserts:
    test_type<char, char>();
    test_type<int, char>();
    test_type<int, int>();
    test_type<long, int>();
    test_type<long, long>();
    test_type<long long, long>();
    test_type<long long, long long>();
    test_type<unsigned char, unsigned char>();
    test_type<unsigned int, unsigned char>();
    test_type<unsigned int, unsigned int>();
    test_type<unsigned long, unsigned int>();
    test_type<unsigned long, unsigned long>();
    test_type<unsigned long long, unsigned long>();
    test_type<unsigned long long, unsigned long long>();

    // Should fire asserts:
    test_type<char, int>(true);
    test_type<int, long>(true);
    test_type<long, long long>(true);
    test_type<char, long long>(true);
    test_type<char, long>(true);
    test_type<unsigned char, unsigned int>(true);
    test_type<unsigned int, unsigned long>(true);
    test_type<unsigned long, unsigned long long>(true);
    test_type<unsigned char, unsigned long long>(true);
    test_type<unsigned char, unsigned long>(true);

    // Should not fire asserts:
    test_type<int, unsigned char>();
    test_type<long, unsigned char>();
    test_type<long, unsigned short>();
    test_type<long, unsigned int>();
    test_type<long long, unsigned char>();
    test_type<long long, unsigned short>();
    test_type<long long, unsigned int>();
    // test_type<long long, unsigned long>();

    // Should fire asserts:
    test_type<unsigned long long, char>(true);
    test_type<unsigned long long, short>(true);
    test_type<unsigned long long, int>(true);
    test_type<unsigned long long, long>(true);
    test_type<char, unsigned char>(true);
    test_type<unsigned int, char>(true);
    test_type<unsigned long, char>(true);
    test_type<unsigned long, short>(true);
    test_type<unsigned long, int>(true);
    test_type<int, unsigned int>(true);
    test_type<long, unsigned long>(true);
    test_type<unsigned char, char>(true);
    test_type<unsigned int, int>(true);
    test_type<unsigned long, long>(true);
    test_type<int, unsigned long>(true);
    test_type<unsigned int, long>(true);
    test_type<char, unsigned int>(true);
    test_type<unsigned char, int>(true);

    // Should fire asserts:
    test_val<unsigned char>((char)-1, true);
    test_val<unsigned short>((short)-1, true);
    test_val<unsigned int>((int)-1, true);
    test_val<unsigned long>((long)-1, true);
    test_val<unsigned long long>((long long)-1, true);

    using namespace std;

    // Should not fire asserts:
    test_val<unsigned char>(numeric_limits<unsigned char>::max());
    test_val<unsigned char>(numeric_limits<unsigned char>::min());
    test_val<unsigned short>(numeric_limits<unsigned short>::max());
    test_val<unsigned short>(numeric_limits<unsigned short>::min());
    test_val<unsigned int>(numeric_limits<unsigned int>::max());
    test_val<unsigned int>(numeric_limits<unsigned int>::min());
    test_val<unsigned long>(numeric_limits<unsigned long>::max());
    test_val<unsigned long>(numeric_limits<unsigned long>::min());
    test_val<unsigned long long>(numeric_limits<unsigned long long>::max());
    test_val<unsigned long long>(numeric_limits<unsigned long long>::min());

    // Should fire asserts:
    test_val<unsigned char>(
        (unsigned short)numeric_limits<unsigned char>::max() + 1, true);
    test_val<unsigned char>(
        (unsigned short)numeric_limits<unsigned char>::min() - 1, true);
    test_val<unsigned short>(
        (unsigned int)numeric_limits<unsigned short>::max() + 1, true);
    test_val<unsigned short>(
        (unsigned int)numeric_limits<unsigned short>::min() - 1, true);
    test_val<unsigned int>(
        (unsigned long)numeric_limits<unsigned int>::max() + 1, true);
    test_val<unsigned int>(
        (unsigned long)numeric_limits<unsigned int>::min() - 1, true);
    test_val<unsigned long>(
        (unsigned long long)numeric_limits<unsigned long>::max() + 1, true);
    test_val<unsigned long>(
        (unsigned long long)numeric_limits<unsigned long>::min() - 1, true);
    test_val<unsigned long long>(
        numeric_limits<unsigned long long>::max() + 1, true);
    test_val<unsigned long long>(
        numeric_limits<unsigned long long>::min() - 1, true);

    // Should fire asserts:
    test_val<char>((short)numeric_limits<char>::max() + 1, true);
    test_val<char>((short)numeric_limits<char>::min() - 1, true);
    test_val<short>((int)numeric_limits<short>::max() + 1, true);
    test_val<short>((int)numeric_limits<short>::min() - 1, true);

#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic push
    test_val<int>((long)numeric_limits<int>::max() + 1, true);
    test_val<int>((long)numeric_limits<int>::min() - 1, true);
    test_val<long>((long long)numeric_limits<long>::max() + 1, true);
    test_val<long>((long long)numeric_limits<long>::min() - 1, true);
    test_val<long long>(numeric_limits<long long>::max() + 1, true);
    test_val<long long>(numeric_limits<long long>::min() - 1, true);
#pragma GCC diagnostic pop

    // Should not fire asserts:
    test_val<unsigned char>(
        (unsigned short)numeric_limits<unsigned char>::max());
    test_val<unsigned char>(
        (unsigned short)numeric_limits<unsigned char>::min());
    test_val<unsigned short>(
        (unsigned int)numeric_limits<unsigned short>::max());
    test_val<unsigned short>(
        (unsigned int)numeric_limits<unsigned short>::min());
    test_val<unsigned int>((unsigned long)numeric_limits<unsigned int>::max());
    test_val<unsigned int>((unsigned long)numeric_limits<unsigned int>::min());
    test_val<unsigned long>(
        (unsigned long long)numeric_limits<unsigned long>::max());
    test_val<unsigned long>(
        (unsigned long long)numeric_limits<unsigned long>::min());
    test_val<unsigned long long>(numeric_limits<unsigned long long>::max());
    test_val<unsigned long long>(numeric_limits<unsigned long long>::min());
}

void floating_tests()
{
    // Should not fire asserts:
    test_type<float, float>();
    test_type<double, double>();
    test_type<long double, long double>();

    // Should fire asserts:
    test_type<float, double>(true);
    test_type<double, long double>(true);

    // Should not fire asserts:
    test_val<float>(0.f);
    test_val<float>(0.0);
    test_val<float>(0.0l);
    test_val<double>(0.f);
    test_val<double>(0.0);
    test_val<double>(0.0l);
    test_val<long double>(0.f);
    test_val<long double>(0.0);
    test_val<long double>(0.0l);

    // Should not fire asserts:
    test_val<float>(1.f);
    test_val<float>(1.0);
    test_val<float>(1.0l);
    test_val<double>(1.f);
    test_val<double>(1.0);
    test_val<double>(1.0l);
    test_val<long double>(1.f);
    test_val<long double>(1.0);
    test_val<long double>(1.0l);

    // Should not fire asserts:
    test_val<float>(-1.f);
    test_val<float>(-1.0);
    test_val<float>(-1.0l);
    test_val<double>(-1.f);
    test_val<double>(-1.0);
    test_val<double>(-1.0l);
    test_val<long double>(-1.f);
    test_val<long double>(-1.0);
    test_val<long double>(-1.0l);

    // Should fire asserts:
    test_val<float>(std::numeric_limits<float>::max() +
                        std::numeric_limits<float>::epsilon(),
        true);
    test_val<float>(std::numeric_limits<float>::lowest() -
                        std::numeric_limits<float>::epsilon(),
        true);
    test_val<double>(std::numeric_limits<double>::max() +
                         std::numeric_limits<double>::epsilon(),
        true);
    test_val<double>(std::numeric_limits<double>::lowest() -
                         std::numeric_limits<double>::epsilon(),
        true);
    test_val<long double>(std::numeric_limits<long double>::max() +
                              std::numeric_limits<long double>::epsilon(),
        true);
    test_val<long double>(std::numeric_limits<long double>::lowest() -
                              std::numeric_limits<long double>::epsilon(),
        true);

    // Should not fire asserts:
    test_val<float>(std::numeric_limits<float>::max());
    test_val<float>(std::numeric_limits<float>::lowest());
    test_val<double>(std::numeric_limits<double>::max());
    test_val<double>(std::numeric_limits<double>::lowest());
    test_val<long double>(std::numeric_limits<long double>::max());
    test_val<long double>(std::numeric_limits<long double>::lowest());
}

void mixed_tests()
{
    // Should not fire asserts:
    test_type<float, int>();
    test_type<float, long>();
    test_type<float, long long>();
    test_type<double, int>();
    test_type<double, long>();
    test_type<double, long long>();
    test_type<long double, int>();
    test_type<long double, long>();
    test_type<long double, long long>();

    // Should fire asserts:
    test_type<char, float>(true);
    test_type<short, float>(true);
    test_type<int, float>(true);
    test_type<long, float>(true);
    test_type<char, double>(true);
    test_type<short, double>(true);
    test_type<int, double>(true);
    test_type<long, double>(true);
    test_type<char, long double>(true);
    test_type<short, long double>(true);
    test_type<int, long double>(true);
    test_type<long, long double>(true);

    // Should not fire asserts:
    test_val<float>((char)0);
    test_val<float>((char)-1);
    test_val<float>((char)1);
    test_val<float>((unsigned char)0);
    test_val<float>((unsigned char)-1);
    test_val<float>((unsigned char)1);
    test_val<float>((int)0);
    test_val<float>((int)-1);
    test_val<float>((int)1);
    test_val<float>((unsigned int)0);
    test_val<float>((unsigned int)-1);
    test_val<float>((unsigned int)1);

    // Should not fire asserts:
    test_val<double>((char)0);
    test_val<double>((char)-1);
    test_val<double>((char)1);
    test_val<double>((unsigned char)0);
    test_val<double>((unsigned char)-1);
    test_val<double>((unsigned char)1);
    test_val<double>((int)0);
    test_val<double>((int)-1);
    test_val<double>((int)1);
    test_val<double>((unsigned int)0);
    test_val<double>((unsigned int)-1);
    test_val<double>((unsigned int)1);

    // Should not fire asserts:
    test_val<float>(std::numeric_limits<char>::lowest());
    test_val<float>(std::numeric_limits<char>::max());
    test_val<float>(std::numeric_limits<unsigned char>::lowest());
    test_val<float>(std::numeric_limits<unsigned char>::max());
    test_val<float>(std::numeric_limits<int>::lowest());
    test_val<float>(std::numeric_limits<int>::max());
    test_val<float>(std::numeric_limits<unsigned int>::lowest());
    test_val<float>(std::numeric_limits<unsigned int>::max());
    test_val<float>(std::numeric_limits<long>::lowest());
    test_val<float>(std::numeric_limits<long>::max());
    test_val<float>(std::numeric_limits<unsigned long>::lowest());
    test_val<float>(std::numeric_limits<unsigned long>::max());
    test_val<double>(std::numeric_limits<char>::lowest());

    // Should not fire asserts:
    test_val<double>(std::numeric_limits<char>::max());
    test_val<double>(std::numeric_limits<unsigned char>::lowest());
    test_val<double>(std::numeric_limits<unsigned char>::max());
    test_val<double>(std::numeric_limits<int>::lowest());
    test_val<double>(std::numeric_limits<int>::max());
    test_val<double>(std::numeric_limits<unsigned int>::lowest());
    test_val<double>(std::numeric_limits<unsigned int>::max());
    test_val<double>(std::numeric_limits<long>::lowest());
    test_val<double>(std::numeric_limits<long>::max());
    test_val<double>(std::numeric_limits<unsigned long>::lowest());
    test_val<double>(std::numeric_limits<unsigned long>::max());

    // Should not fire asserts:
    test_val<char>(0.f);
    test_val<char>(1.f);
    test_val<char>(-1.f);
    test_val<char>(0.0);
    test_val<char>(1.0);
    test_val<char>(-1.0);
    test_val<char>(0.l);
    test_val<char>(1.l);
    test_val<char>(-1.l);

    // Should not fire asserts:
    test_val<int>(0.f);
    test_val<int>(1.f);
    test_val<int>(-1.f);
    test_val<int>(0.0);
    test_val<int>(1.0);
    test_val<int>(-1.0);
    test_val<int>(0.l);
    test_val<int>(1.l);
    test_val<int>(-1.l);

    // Should not fire asserts:
    test_val<long>(0.f);
    test_val<long>(1.f);
    test_val<long>(-1.f);
    test_val<long>(0.0);
    test_val<long>(1.0);
    test_val<long>(-1.0);
    test_val<long>(0.l);
    test_val<long>(1.l);
    test_val<long>(-1.l);

    // Should not fire asserts:
    test_val<unsigned char>(0.f);
    test_val<unsigned char>(1.f);
    test_val<unsigned char>(0.0);
    test_val<unsigned char>(1.0);
    test_val<unsigned char>(0.l);
    test_val<unsigned char>(1.l);

    // Should not fire asserts:
    test_val<unsigned int>(0.f);
    test_val<unsigned int>(1.f);
    test_val<unsigned int>(0.0);
    test_val<unsigned int>(1.0);
    test_val<unsigned int>(0.l);
    test_val<unsigned int>(1.l);

    // Should not fire asserts:
    test_val<unsigned long>(0.f);
    test_val<unsigned long>(1.f);
    test_val<unsigned long>(0.0);
    test_val<unsigned long>(1.0);
    test_val<unsigned long>(0.l);
    test_val<unsigned long>(1.l);
}

TEST_MAIN()
{

    int i = 1;

    TEST_ASSERT(i == 1);
    TEST_ASSERT(vrm::core::to_int(i) == 1);
    TEST_ASSERT(vrm::core::to_float(i) == 1.f);
    TEST_ASSERT(vrm::core::to_double(i) == 1);
    TEST_ASSERT(vrm::core::to_sz_t(i) == 1);
    TEST_ASSERT(vrm::core::to_num<long>(i) == 1.f);

    integral_tests();
    floating_tests();
    mixed_tests();

    // Will fire assertion:
    // TEST_ASSERT(to_size_t<int>(int(-1)) == -1);

    {
        using namespace vrm::core;

        (void)to_char(1);
        (void)to_short(1);
        (void)to_int(1);
        (void)to_long(1);
        (void)to_llong(1);
        (void)to_uchar(1);
        (void)to_ushort(1);
        (void)to_uint(1);
        (void)to_ulong(1);
        (void)to_ullong(1);
        (void)to_i8(1);
        (void)to_i16(1);
        (void)to_i32(1);
        (void)to_i64(1);
        (void)to_ui8(1);
        (void)to_ui16(1);
        (void)to_ui32(1);
        (void)to_ui64(1);
        (void)to_sz_t(1);
        (void)to_float(1);
        (void)to_double(1);
        (void)to_ldouble(1);
    }

    return 0;
}
