#include "../../../utils/test_res_utils.hpp"

namespace test
{
    // Weak from shared, check use count
    void weak_0()
    {
        assert_ck(0, 0);

        {
            auto h = test_behavior::init();
            assert_ck(1, 0);

            shared_test s0(h);
            assert_ck(1, 0);

            weak_test w0(s0);
            assert_ck(1, 0);

            assert(!w0.expired());
            assert(w0.use_count() == 1);
            assert(s0.use_count() == w0.use_count());
        }

        assert_ck(1, 1);
    }

    // Copy weak, access via shared
    void weak_1()
    {
        assert_ck(0, 0);

        {
            shared_test s0(test_behavior::init());
            assert_ck(1, 0);

            weak_test w0(s0);
            assert_ck(1, 0);

            auto w1(w0);
            assert_ck(1, 0);

            assert(!w0.expired());
            assert(w0.use_count() == 1);

            assert(!w1.expired());
            assert(w1.use_count() == 1);

            assert(w0.lock().get() == w1.lock().get());
        }

        assert_ck(1, 1);
    }

    // Use count
    void weak_2()
    {
        assert_ck(0, 0);

        {
            shared_test s0(test_behavior::init());
            assert_ck(1, 0);

            weak_test w0(s0);
            assert_ck(1, 0);

            assert(w0.use_count() == 1);
        }

        assert_ck(1, 1);
    }

    // Expired
    void weak_3()
    {
        assert_ck(0, 0);

        {
            weak_test w0;
            assert(w0.expired());

            {
                shared_test s0(test_behavior::init());
                assert_ck(1, 0);

                w0 = s0;
                assert_ck(1, 0);

                assert(!w0.expired());
            }

            assert(w0.expired());
        }

        assert_ck(1, 1);
    }

    // Uniqueness
    void weak_4()
    {
        assert_ck(0, 0);

        {
            shared_test s0(test_behavior::init());
            assert_ck(1, 0);

            weak_test w0(s0);
            assert_ck(1, 0);

            assert(s0.unique());
            assert(!w0.lock().unique());
        }

        assert_ck(1, 1);
    }

    // Swap test
    void weak_5()
    {
        assert_ck(0, 0);

        {
            shared_test s0(test_behavior::init());
            assert_ck(1, 0);

            weak_test w0(s0);
            assert_ck(1, 0);

            shared_test s1(test_behavior::init());
            assert_ck(2, 0);

            weak_test w1(s1);
            assert_ck(2, 0);

            auto old0(s0.get());
            auto old1(s1.get());
            assert_ck(2, 0);

            assert(w0.lock().get() == old0);
            assert(w1.lock().get() == old1);

            w0.swap(w1);
            assert_ck(2, 0);

            assert(w0.lock().get() == old1);
            assert(w1.lock().get() == old0);

            (void)old0;
            (void)old1;
        }

        assert_ck(2, 2);
    }

    // Decrement weak count
    void weak_6()
    {
        assert_ck(0, 0);

        {
            shared_test s0(test_behavior::init());
            assert_ck(1, 0);

            assert(s0.use_count() == 1);

            weak_test w0(s0);

            assert(s0.use_count() == 1);
            assert(!w0.expired());

            {
                weak_test w1(w0);
                assert(s0.use_count() == 1);
                assert(!w0.expired());
                assert(!w1.expired());
            }

            assert(s0.use_count() == 1);
            assert(!w0.expired());
        }

        assert_ck(1, 1);
    }
} // namespace test

TEST_MAIN()
{
    using namespace test;

    RUN_T(weak_0);
    RUN_T(weak_1);
    RUN_T(weak_2);
    RUN_T(weak_3);
    RUN_T(weak_4);
    RUN_T(weak_5);
    RUN_T(weak_6);
}
