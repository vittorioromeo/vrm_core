#include "../../../utils/test_utils.hpp"
#include <vrm/core/casts/arithmetic.hpp>
#include <vrm/core/experimental/multi_vector.hpp>

volatile int cc = 0;
volatile int dd = 0;
volatile int copies = 0;

struct ctorer
{
};

struct item
{
    int l;
    item()
    {
        ++cc;
    }
    item(ctorer)
    {
        ++cc;
    }

    item(const item&)
    {
        ++copies;
    }
    item(item&&) = delete;

    item& operator=(const item&)
    {
        ++copies;
        return *this;
    }

    ~item()
    {
        ++dd;
    }
};


int main()
{
    using namespace vrm::core;

    {
        {
            cc = dd = copies = 0;

            using mb_type = multi_resizable_buffer<resizable_buffer<int>,
                resizable_buffer<float>, resizable_buffer<item>>;

            using mv_type = impl::multi_vector<mb_type>;

            mv_type mv;

            TEST_ASSERT_OP(mv.capacity(), ==, mv_type::initial_capacity());
            TEST_ASSERT_OP(mv.size(), ==, to_sz_t(0));
            TEST_ASSERT_OP(cc, ==, 0);
            TEST_ASSERT_OP(copies, ==, 0);
            TEST_ASSERT_OP(dd, ==, 0);

            static_assert(
                std::is_same<decltype(mv[0]), mv_type::value_reference_tuple>{},
                "");

            static_assert(
                std::is_same<decltype(static_cast<const mv_type&>(mv)[0]),
                    mv_type::const_value_reference_tuple>{},
                "");

            mv.reserve(100);

            TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
            TEST_ASSERT_OP(mv.size(), ==, to_sz_t(0));
            TEST_ASSERT_OP(cc, ==, 0);
            TEST_ASSERT_OP(copies, ==, 0);
            TEST_ASSERT_OP(dd, ==, 0);

            mv.resize(50);

            TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
            TEST_ASSERT_OP(mv.size(), ==, to_sz_t(50));
            TEST_ASSERT_OP(cc, ==, 50);
            TEST_ASSERT_OP(copies, ==, 0);
            TEST_ASSERT_OP(dd, ==, 0);

            mv.resize(100);

            TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
            TEST_ASSERT_OP(mv.size(), ==, to_sz_t(100));
            TEST_ASSERT_OP(cc, ==, 100);
            TEST_ASSERT_OP(copies, ==, 0);
            TEST_ASSERT_OP(dd, ==, 0);

            mv.resize(150);

            TEST_ASSERT_OP(mv.capacity(), >, to_sz_t(100));
            TEST_ASSERT_OP(mv.size(), ==, to_sz_t(150));
            TEST_ASSERT_OP(cc, ==, 150);
            TEST_ASSERT_OP(copies, ==, 100);
            TEST_ASSERT_OP(dd, ==, 100);
        }

        TEST_ASSERT_OP(cc, ==, 150);
        TEST_ASSERT_OP(copies, ==, 100);
        TEST_ASSERT_OP(dd, ==, 250);
    }

    {
        cc = dd = copies = 0;

        using mb_type = multi_resizable_buffer<resizable_buffer<int>,
            resizable_buffer<float>, resizable_buffer<item>>;

        using mv_type = impl::multi_vector<mb_type>;

        mv_type mv;

        TEST_ASSERT_OP(mv.capacity(), ==, mv_type::initial_capacity());
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(0));
        TEST_ASSERT_OP(cc, ==, 0);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        static_assert(
            std::is_same<decltype(mv[0]), mv_type::value_reference_tuple>{},
            "");

        static_assert(std::is_same<decltype(static_cast<const mv_type&>(mv)[0]),
                          mv_type::const_value_reference_tuple>{},
            "");

        mv.reserve(100);

        TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(0));
        TEST_ASSERT_OP(cc, ==, 0);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        mv.unsafe_emplace_back(
            std::make_tuple(1), std::make_tuple(1.f), std::make_tuple());

        TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(1));
        TEST_ASSERT_OP(cc, ==, 1);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        {
            const auto& x(mv[0]);
            TEST_ASSERT_OP(std::get<int&>(x), ==, 1);
            TEST_ASSERT_OP(std::get<float&>(x), ==, 1.f);
        }

        mv.unsafe_emplace_back(
            std::make_tuple(10), std::make_tuple(21.f), std::make_tuple());

        TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(2));
        TEST_ASSERT_OP(cc, ==, 2);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        {
            const auto& x(mv[1]);
            TEST_ASSERT_OP(std::get<int&>(x), ==, 10);
            TEST_ASSERT_OP(std::get<float&>(x), ==, 21.f);
        }

        mv.unsafe_push_back(10, 21.f, ctorer{});

        TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(3));
        TEST_ASSERT_OP(cc, ==, 3);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        {
            const auto& x(mv[2]);
            TEST_ASSERT_OP(std::get<int&>(x), ==, 10);
            TEST_ASSERT_OP(std::get<float&>(x), ==, 21.f);
        }



        decltype(mv)::value_tuple p(mv.back());

        TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(3));
        TEST_ASSERT_OP(cc, ==, 3);
        TEST_ASSERT_OP(copies, ==, 1);
        TEST_ASSERT_OP(dd, ==, 0);

        {
            const auto& x(mv[2]);
            TEST_ASSERT_OP(std::get<int&>(x), ==, 10);
            TEST_ASSERT_OP(std::get<float&>(x), ==, 21.f);

            TEST_ASSERT_OP(std::get<int>(p), ==, 10);
            TEST_ASSERT_OP(std::get<float>(p), ==, 21.f);
        }

        mv.pop_back();

        TEST_ASSERT_OP(mv.capacity(), ==, to_sz_t(100));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(2));
        TEST_ASSERT_OP(cc, ==, 3);
        TEST_ASSERT_OP(copies, ==, 1);
        TEST_ASSERT_OP(dd, ==, 1);

        {
            TEST_ASSERT_OP(std::get<int>(p), ==, 10);
            TEST_ASSERT_OP(std::get<float>(p), ==, 21.f);
        }
    }

    {
        cc = dd = copies = 0;

        using mb_type = multi_resizable_buffer<resizable_buffer<int>,
            resizable_buffer<float>, resizable_buffer<item>>;

        using mv_type = impl::multi_vector<mb_type>;

        mv_type mv;

        TEST_ASSERT_OP(mv.capacity(), ==, mv_type::initial_capacity());
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(0));
        TEST_ASSERT_OP(cc, ==, 0);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        static_assert(
            std::is_same<decltype(mv[0]), mv_type::value_reference_tuple>{},
            "");

        static_assert(std::is_same<decltype(static_cast<const mv_type&>(mv)[0]),
                          mv_type::const_value_reference_tuple>{},
            "");

        mv.emplace_back(
            std::make_tuple(1), std::make_tuple(1.f), std::make_tuple());

        TEST_ASSERT_OP(mv.capacity(), >, to_sz_t(0));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(1));
        TEST_ASSERT_OP(cc, ==, 1);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        {
            const auto& x(mv[0]);
            TEST_ASSERT_OP(std::get<int&>(x), ==, 1);
            TEST_ASSERT_OP(std::get<float&>(x), ==, 1.f);
        }

        mv.emplace_back(
            std::make_tuple(10), std::make_tuple(21.f), std::make_tuple());

        TEST_ASSERT_OP(mv.capacity(), >, to_sz_t(0));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(2));
        TEST_ASSERT_OP(cc, ==, 2);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        {
            const auto& x(mv[1]);
            TEST_ASSERT_OP(std::get<int&>(x), ==, 10);
            TEST_ASSERT_OP(std::get<float&>(x), ==, 21.f);
        }

        mv.push_back(10, 21.f, ctorer{});

        TEST_ASSERT_OP(mv.capacity(), >, to_sz_t(0));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(3));
        TEST_ASSERT_OP(cc, ==, 3);
        TEST_ASSERT_OP(copies, ==, 0);
        TEST_ASSERT_OP(dd, ==, 0);

        {
            const auto& x(mv[2]);
            TEST_ASSERT_OP(std::get<int&>(x), ==, 10);
            TEST_ASSERT_OP(std::get<float&>(x), ==, 21.f);
        }



        decltype(mv)::value_tuple p(mv.back());

        TEST_ASSERT_OP(mv.capacity(), >, to_sz_t(0));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(3));
        TEST_ASSERT_OP(cc, ==, 3);
        TEST_ASSERT_OP(copies, ==, 1);
        TEST_ASSERT_OP(dd, ==, 0);

        {
            const auto& x(mv[2]);
            TEST_ASSERT_OP(std::get<int&>(x), ==, 10);
            TEST_ASSERT_OP(std::get<float&>(x), ==, 21.f);

            TEST_ASSERT_OP(std::get<int>(p), ==, 10);
            TEST_ASSERT_OP(std::get<float>(p), ==, 21.f);
        }

        mv.pop_back();

        TEST_ASSERT_OP(mv.capacity(), >, to_sz_t(0));
        TEST_ASSERT_OP(mv.size(), ==, to_sz_t(2));
        TEST_ASSERT_OP(cc, ==, 3);
        TEST_ASSERT_OP(copies, ==, 1);
        TEST_ASSERT_OP(dd, ==, 1);

        {
            TEST_ASSERT_OP(std::get<int>(p), ==, 10);
            TEST_ASSERT_OP(std::get<float>(p), ==, 21.f);
        }
    }


    return 0;
}
