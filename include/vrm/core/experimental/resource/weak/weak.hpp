// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/shared.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            // TODO:
            template <typename TBehavior, typename TLockPolicy>
            class weak
            {
                template <typename, typename>
                friend class shared;

            public:
                using behavior_type = TBehavior;
                using handle_type = typename behavior_type::handle_type;
                using ref_counter_type = impl::shared_ref_counter;
                using lock_policy_type = TLockPolicy;
                using shared_type = shared<TBehavior, TLockPolicy>;

            private:
                handle_type _handle{behavior_type::null_handle()};
                ref_counter_type _ref_counter;

            public:
                weak() noexcept;
                weak(const weak& rhs) noexcept;
                weak(const shared_type& rhs) noexcept;
                weak(weak&& rhs) noexcept;

                auto& operator=(const weak& rhs) noexcept;
                auto& operator=(const shared_type& rhs) noexcept;
                auto& operator=(weak&& rhs) noexcept;

                ~weak();

                void swap(weak& rhs) noexcept;
                void reset() noexcept;

                auto use_count() const noexcept;
                auto expired() const noexcept;

                auto lock() const noexcept;

                template <typename>
                friend void swap(weak& lhs, weak& rhs) noexcept;
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
