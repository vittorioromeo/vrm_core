// Copyright (c) 2015-2017 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include "./test_utils.hpp"
#include <vrm/core/experimental/resource.hpp>

namespace test
{
    using namespace vrm::core;

    volatile int created{0};
    volatile int killed{0};

    struct test_behavior
    {
        using handle_type = int;

        test_behavior() = delete;

        static handle_type null_handle()
        {
            return -1;
        }

        static handle_type init()
        {
            ++created;

            static int next{0};
            return next++;
        }

        static void deinit(const handle_type& h)
        {
            if(h != null_handle()) ++killed;
        }
    };
    static_assert(resource::is_valid_behavior<test_behavior>{} );

    using unique_test = resource::unique<test_behavior>;
    using shared_test = resource::shared<test_behavior>;

    // TODO:
    using weak_test = resource::impl::weak<test_behavior,
        resource::impl::shared_lock_policy::none>;

    void assert_ck(int a_created, int a_killed)
    {
        bool failed = false;

        if(created != a_created) failed = true;

        if(killed != a_killed) failed = true;

        if(failed)
        {
            std::cout << "created: " << created << " (expected:" << a_created
                      << ")\n";
            std::cout << "killed: " << killed << " (expected:" << a_killed
                      << ")\n";
            std::terminate();
        }
    }

    template <typename TF>
    void run(const char* title, TF&& f)
    {
        std::cout << "Running test: " << title << "\n";

        created = killed = 0;
        f();
    }
} // namespace test

#define RUN_T(x) run(#x, &x)
