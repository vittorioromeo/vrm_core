#pragma once

// TODO: workflow module
// <vrm/core/workflow/test_utils.hpp>
// <vrm/core/workflow/test_debug.hpp>
// VRMCW_PRINT_SIZE(x) -> VRM_CORE_WORKFLOW_PRINT_SIZE(x) => "[VRMCW] sizeof(x):
// 1234"
// VRMCW_PRINT_VAR(x) -> VRM_CORE_WORKFLOW_PRINT_VAR(x) => "[VRMCW] x: 44"
// VRMCW_TEST(x) -> VRM_CORE_WORKFLOW_TEST(x) -> TEST_ASSERT(x)
// VRMCW_TEST_OP(l, op, r) -> VRM_CORE_WORKFLOW_TEST_OP(l, op, r) ->
// TEST_ASSERT_OP(l, op, r)

#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#ifndef FWD
#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)
#endif

#define TEST_CONST __attribute__((const))
#define TEST_MAIN(...) int TEST_CONST main(__VA_ARGS__)

#define TEST_IMPL_DEPARENS(...) __VA_ARGS__

#define SA_SAME(value, type) \
    static_assert(           \
        std::is_same<TEST_IMPL_DEPARENS value, TEST_IMPL_DEPARENS type>{}, "")

#define SA_TYPE(value, type) \
    static_assert(std::is_same<decltype value, TEST_IMPL_DEPARENS type>{}, "")

#define VRM_CORE_LIKELY(...) __builtin_expect(!!(__VA_ARGS__), 1)

namespace test_impl
{
    namespace impl
    {
        template <typename...>
        using void_t = void;

        template <typename T, typename = void>
        struct can_print_t : std::false_type
        {
        };

        template <typename T>
        struct can_print_t<T, void_t<decltype(std::declval<std::ostream&>()
                                              << std::declval<T>())>>
            : std::true_type
        {
        };

        template <typename T>
        constexpr can_print_t<T> can_print{};
    }

    namespace impl
    {
        inline auto& get_oss() noexcept
        {
            static std::ostringstream oss;
            return oss;
        }

        inline auto& clear_and_get_oss() noexcept
        {
            auto& oss(get_oss());
            oss.str("");
            return oss;
        }

        [[noreturn]] inline void fail() noexcept
        {
            std::cout << get_oss().str() << std::endl;
            std::terminate();
        }

        template <typename TStream>
        inline void output_line(TStream& s, int line)
        {
            s << "line: " << line << "\n";
        }

        template <typename TStream>
        inline void output_expr(TStream& s, const char* expr)
        {
            s << "expr: " << expr << "\n";
        }

        template <typename TStream, typename T>
        inline void output_result(
            TStream& s, const T& lhs_result, std::true_type)
        {
            s << "result: " << lhs_result << "\n";
        }

        template <typename TStream, typename T>
        inline void output_result(TStream&, const T&, std::false_type)
        {
        }

        template <typename TStream>
        inline void output_expected(TStream& s, const char* expected)
        {
            s << "expected: " << expected << "\n";
        }

        template <typename TStream, typename T>
        inline void output_expected(TStream& s, const char* expected,
            const T& rhs_result, std::true_type)
        {
            s << "expected: " << expected << " -> " << rhs_result << "\n";
        }

        template <typename TStream, typename T>
        inline void output_expected(
            TStream&, const char*, const T&, std::false_type)
        {
        }

        template <typename TF>
        inline void do_test(bool x, TF&& f)
        {
            if(VRM_CORE_LIKELY(x)) return;

            auto& error(impl::clear_and_get_oss());
            f(error);
            impl::fail();
        }
    }

    template <typename T>
    inline void test_expr(
        int line, bool x, T&& lhs_result, const char* expr) noexcept
    {
        impl::do_test(x, [&](auto& s) {
            impl::output_line(s, line);
            impl::output_expr(s, expr);
            impl::output_result(s, lhs_result, impl::can_print<T>);
        });
    }

    template <typename TLhs, typename TRhs>
    inline void test_op(int line, bool x, TLhs&& lhs_result, TRhs&& rhs_result,
        const char* expr, const char* expected)
    {
        impl::do_test(x, [&](auto& s) {
            impl::output_line(s, line);
            impl::output_expr(s, expr);
            impl::output_result(s, lhs_result, impl::can_print<TLhs>);
            impl::output_expected(
                s, expected, rhs_result, impl::can_print<TRhs>);
        });
    }
}

#define TEST_ASSERT(expr)                                  \
    do                                                     \
    {                                                      \
        auto _t_x(expr);                                   \
                                                           \
        test_impl::test_expr(__LINE__, _t_x, expr, #expr); \
    } while(false)

#define TEST_ASSERT_OP(lhs, op, rhs)                                           \
    do                                                                         \
    {                                                                          \
        using ct = std::common_type_t<decltype(lhs), decltype(rhs)>;           \
                                                                               \
        auto _t_xl(lhs);                                                       \
        auto _t_xr(rhs);                                                       \
                                                                               \
        auto _t_x(ct(_t_xl) op ct(_t_xr));                                     \
                                                                               \
        test_impl::test_op(__LINE__, _t_x, _t_xl, _t_xr, #lhs #op #rhs, #rhs); \
    } while(false)



#include <map>
#include <string>

namespace testing
{
    namespace impl
    {
        auto& get_ostream() noexcept
        {
            return std::cout;
        }

        using obj_id = std::string;

        struct stats
        {
            int _ctors = 0;
            int _dtors = 0;
            int _copies = 0;
            int _moves = 0;
        };

        using stat_map = std::map<obj_id, stats>;

        class operation_context;

        template <typename T>
        class tracked_object
        {
        private:
            operation_context* _ctx;
            obj_id _id;
            T _inner;

            auto& get_stats();

            void inc_ctor() noexcept
            {
                ++(get_stats()._ctors);
            }

            void inc_dtor() noexcept
            {
                ++(get_stats()._dtors);
            }

            void inc_copy() noexcept
            {
                ++(get_stats()._copies);
            }

            void inc_move() noexcept
            {
                ++(get_stats()._moves);
            }


        public:
            template <typename... Ts>
            tracked_object(operation_context& ctx, obj_id id, Ts&&... xs)
                : _ctx{&ctx}, _id{std::move(id)}, _inner(FWD(xs)...)
            {
                get_ostream() << _id << "()\n";
                inc_ctor();
            }

            ~tracked_object()
            {
                get_ostream() << "~" << _id << "()\n";
                inc_dtor();
            }


            tracked_object(const tracked_object& rhs)
                : _ctx{rhs._ctx}, _id{rhs._id}, _inner{rhs._inner}
            {
                get_ostream() << _id << "(const" << _id << "&)\n";
                inc_copy();
            }

            tracked_object& operator=(const tracked_object& rhs)
            {
                _ctx = rhs._ctx;
                _id = rhs._id;
                _inner = rhs._inner;

                get_ostream() << "tracked_object& operator=(const " << _id
                              << "&)\n";
                inc_copy();
                return *this;
            }

            tracked_object(tracked_object&& rhs)
                : _ctx{std::move(rhs._ctx)}, _id{rhs._id},
                  _inner{std::move(rhs._inner)}
            {
                get_ostream() << _id << "(" << _id << "&&)\n";
                inc_move();
            }

            tracked_object& operator=(tracked_object&& rhs)
            {
                _ctx = std::move(rhs._ctx);
                _id = std::move(rhs._id);
                _inner = std::move(rhs._inner);

                get_ostream() << _id << "& operator=(" << _id << "&&)\n";
                inc_move();
                return *this;
            }

            auto& get() noexcept
            {
                return _inner;
            }

            const auto& get() const noexcept
            {
                return _inner;
            }
        };

        namespace obj
        {
            struct anything
            {
            };

            struct no_copy
            {
                no_copy(const no_copy&) = delete;
                no_copy& operator=(const no_copy&) = delete;
            };

            struct no_move
            {
                no_move(no_move&&) = delete;
                no_move& operator=(no_move&&) = delete;
            };

            struct no_copy_no_move : no_copy, no_move
            {
            };
        }

        class matcher;
        class matcher_branch;

        class matcher_branch_logic
        {
        private:
            matcher& _m;
            matcher_branch& _mb;
            const int& _v;

        public:
            matcher_branch_logic(matcher& m, matcher_branch& mb, const int& v)
                : _m{m}, _mb{mb}, _v{v}
            {
            }

            auto& exactly(int x)
            {
                get_ostream() << "exactly `" << x << "`\n";
                TEST_ASSERT_OP(_v, ==, x);
                return _mb;
            }

            auto& more_than(int x)
            {
                get_ostream() << "more than `" << x << "`\n";
                TEST_ASSERT_OP(_v, >, x);
                return _mb;
            }

            auto& less_than(int x)
            {
                get_ostream() << "less than `" << x << "`\n";
                TEST_ASSERT_OP(_v, <, x);
                return _mb;
            }

            template <typename TF>
            auto& satisfies(TF&& f)
            {
                get_ostream() << "satisfying `f`\n";
                TEST_ASSERT(f(_v));
                return _mb;
            }
        };

        class matcher_branch
        {
        private:
            matcher& _m;
            const obj_id& _id;
            const stats& _s;

        public:
            matcher_branch(matcher& m, const obj_id& id, const stats& s)
                : _m{m}, _id{id}, _s{s}
            {
            }

#define DEFINE_INTERFACE_FOR(name, member)                                  \
    auto name() noexcept                                                    \
    {                                                                       \
        get_ostream() << "Checking " << _id << "'s " << #name << " to be "; \
        return matcher_branch_logic{_m, *this, _s.member};                  \
    }                                                                       \
                                                                            \
    auto name(int x) noexcept                                               \
    {                                                                       \
        return name().exactly(x);                                           \
    }                                                                       \
                                                                            \
    auto no_##name() noexcept                                               \
    {                                                                       \
        return name(0);                                                     \
    }

            DEFINE_INTERFACE_FOR(ctors, _ctors)
            DEFINE_INTERFACE_FOR(dtors, _dtors)
            DEFINE_INTERFACE_FOR(copies, _copies)
            DEFINE_INTERFACE_FOR(moves, _moves)

            auto expect_that(const obj_id& id);
        };

        class matcher
        {
        private:
            stat_map _stats;

        public:
            matcher(stat_map&& m) : _stats{std::move(m)}
            {
            }

            auto expect_that(const obj_id& id)
            {
                return matcher_branch{*this, id, _stats[id]};
            }
        };

        auto matcher_branch::expect_that(const obj_id& id)
        {
            return _m.expect_that(id);
        }

        class operation_context
        {
            template <typename>
            friend class tracked_object;

            friend auto make_matcher(operation_context&&);

        private:
            stat_map _stats;

            template <typename T, typename... Ts>
            auto make_tracked_object(obj_id id, Ts&&... xs)
            {
                return T{*this, std::move(id), FWD(xs)...};
            }

        public:
#define DEFINE_MAKE_TRACKED_OBJECT(name, type)                        \
    template <typename... Ts>                                         \
    auto name(Ts&&... xs)                                             \
    {                                                                 \
        return make_tracked_object<tracked_object<type>>(FWD(xs)...); \
    }

            DEFINE_MAKE_TRACKED_OBJECT(anything, obj::anything)
            DEFINE_MAKE_TRACKED_OBJECT(no_copy, obj::no_copy)
            DEFINE_MAKE_TRACKED_OBJECT(no_move, obj::no_move)
            DEFINE_MAKE_TRACKED_OBJECT(no_copy_no_move, obj::no_copy_no_move)

#undef DEFINE_MAKE_TRACKED_OBJECT
        };

        template <typename T>
        auto& tracked_object<T>::get_stats()
        {
            return _ctx->_stats[_id];
        }

        auto make_matcher(operation_context&& ctx)
        {
            return matcher{std::move(ctx._stats)};
        }
    }

    template <typename TF>
    auto check_operations(TF&& f)
    {
        impl::operation_context ctx;
        f(ctx);
        return impl::make_matcher(std::move(ctx));
    }
}

/*
expect([](auto& context)
{
    auto x = context.get_tracked_struct<nocopy>("A");


}).that("A").copies(less_than<3>);*/