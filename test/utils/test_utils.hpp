#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <iostream>

#define DEPARENS(...) __VA_ARGS__

#define SA_SAME(value, type) \
    static_assert(std::is_same<DEPARENS value, DEPARENS type>{}, "")

#define SA_TYPE(value, type) \
    static_assert(std::is_same<decltype value, DEPARENS type>{}, "")

namespace test_impl
{
    template <typename T>
    inline void test_assert(bool x, const T& res, const char* expr) noexcept
    {
        using namespace std::literals;

        if(x) return;
        std::ostringstream error;

        error << expr << "\n"
              << "result: " << res << "\n";

        std::cout << error.str() << std::endl;
        std::terminate();
    }

    template <typename TL, typename TR>
    inline void test_assert_expected(int line, bool x, TL&& res,
        TR&& res_r, const char* expr, const char* expected)
    {
        using namespace std::literals;

        if(x) return;
        std::ostringstream error;

        error << "line: " << line << "\n" << expr << "\n"
              << "result: " << res << "\n"
              << "expected: " << expected << " -> " << res_r << "\n";

        std::cout << error.str() << std::endl;
        std::terminate();
    }

    template <typename T>
    inline void test_assert_ns(bool x, const T&, const char* expr) noexcept
    {
        using namespace std::literals;

        if(x) return;
        std::ostringstream error;

        error << expr << "\n";

        std::cout << error.str() << std::endl;
        std::terminate();
    }

    template <typename T>
    inline void test_assert_ns_expected(
        bool x, const T&, const char* expr, const char* expected)
    {
        using namespace std::literals;

        if(x) return;
        std::ostringstream error;

        error << expr << "\n"
              << "expected: " << expected << "\n";

        std::cout << error.str() << std::endl;
        std::terminate();
    }
}

#define TEST_ASSERT(expr)                          \
    do                                             \
    {                                              \
        auto _t_x = expr;                          \
        test_impl::test_assert(_t_x, expr, #expr); \
    } while(false)

#define TEST_ASSERT_OP(lhs, op, rhs)                                      \
    do                                                                    \
    {                                                                     \
        auto&& _t_xl = lhs;                                               \
        auto&& _t_xr = rhs;                                               \
        using ct = std::common_type_t<decltype(lhs), decltype(rhs)>;      \
        auto _t_x = ct(_t_xl) op ct(_t_xr);                               \
        test_impl::test_assert_expected(                                  \
            __LINE__, _t_x, FWD(_t_xl), FWD(_t_xr), #lhs #op #rhs, #rhs); \
    } while(false)

#define TEST_ASSERT_NS(expr)                          \
    do                                                \
    {                                                 \
        auto _t_x = expr;                             \
        test_impl::test_assert_ns(_t_x, expr, #expr); \
    } while(false)

#define TEST_ASSERT_NS_OP(lhs, op, rhs)                                       \
    do                                                                        \
    {                                                                         \
        auto _t_xl = lhs;                                                     \
        auto _t_x = _t_xl op rhs;                                             \
        test_impl::test_assert_ns_expected(_t_x, _t_xl, #lhs #op #rhs, #rhs); \
    } while(false)
