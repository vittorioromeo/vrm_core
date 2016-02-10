// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/fwd.hpp>
#include <vrm/core/experimental/resource/base.hpp>
#include <vrm/core/experimental/resource/shared/metadata.hpp>
#include <vrm/core/experimental/resource/shared/ref_counter.hpp>
#include <vrm/core/experimental/resource/shared/policies.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            /// @brief Resource class with `shared` ownership semantics.
            /// @details A thread-safety policy can be specified as a template
            /// parameter.
            template <typename TBehavior, typename TLockPolicy>
            class shared : public impl::base<TBehavior>, TLockPolicy
            {
                // `weak` is a `friend` of `shared`.
                template <typename, typename>
                friend class weak;

            public:
                using this_type = shared<TBehavior, TLockPolicy>;
                using base_type = impl::base<TBehavior>;
                using behavior_type = typename base_type::behavior_type;
                using handle_type = typename base_type::handle_type;
                using ref_counter_type = impl::shared_ref_counter;
                using lock_policy_type = TLockPolicy;
                using weak_type = weak<TBehavior, TLockPolicy>;

            private:
                using is_nothrow_deinit =
                    bool_<noexcept(std::declval<this_type>().deinit())>;

            private:
                // In addition to an handle, we store a `ref_counter`.
                // It is a class containing a pointer to an heap-allocated
                // shared ownership metadata instance.
                ref_counter_type _ref_counter;

                // Qualified `ref_counter` access methods.
                auto& access_ref_counter() & noexcept;
                const auto& access_ref_counter() const& noexcept;
                auto access_ref_counter() && noexcept;

                void lose_ownership() noexcept(is_nothrow_deinit{});
                void nullify_and_assert() noexcept;
                void acquire_from_null_if_required();
                void acquire_existing_if_required();

            public:
                shared() noexcept = default;
                ~shared() noexcept;

                explicit shared(const handle_type& handle) noexcept;
                explicit shared(const weak_type& handle) noexcept;

                shared(const shared&);
                auto& operator=(const shared&);

                shared(shared&& rhs) noexcept;
                auto& operator=(shared&&) noexcept(is_nothrow_deinit{});

                void reset() noexcept(is_nothrow_deinit{});
                void reset(const handle_type& handle) noexcept(
                    is_nothrow_deinit{});

                void swap(shared& rhs) noexcept;

                auto use_count() const noexcept;
                bool unique() const noexcept;

                template <typename>
                friend bool operator==(
                    const shared& lhs, const shared& rhs) noexcept;

                template <typename>
                friend bool operator!=(
                    const shared& lhs, const shared& rhs) noexcept;

                template <typename>
                friend void swap(shared& lhs, shared& rhs) noexcept;
            };
        }

        template <typename TBehavior>
        using shared = impl::shared<TBehavior, impl::shared_lock_policy::none>;
    }
}
VRM_CORE_NAMESPACE_END
