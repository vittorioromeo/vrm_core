// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include "./metadata.hpp"
#include "./policies.hpp"
#include "./ref_counter.hpp"
#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/base.hpp>
#include <vrm/core/experimental/resource/fwd.hpp>

namespace vrm::core
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
                using is_nothrow_deinit = is_nothrow_deinit_t<TBehavior>;

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
                constexpr shared() noexcept = default;
                ~shared() noexcept;

                /// @brief Acquires ownership of `handle`, if it's not null.
                explicit shared(const handle_type& handle) noexcept;

                /// @brief Acquires ownership of `handle`, if it's not null.
                explicit shared(const weak_type& handle) noexcept;

                /// @brief Acquires ownership of `rhs`'s handle, if it's not
                /// null. `rhs` won't lose its ownership.
                shared(const shared& rhs);

                /// @brief Acquires ownership of `rhs`'s handle, if it's not
                /// null. `rhs` won't lose its ownership.
                auto& operator=(const shared& rhs);

                /// @brief Acquires ownership of `rhs`'s handle, if it's not
                /// null. `rhs` loses its ownership and points to a null handle.
                shared(shared&& rhs) noexcept;

                /// @brief Acquires ownership of `rhs`'s handle, if it's not
                /// null. `rhs` loses its ownership and points to a null handle.
                auto& operator=(shared&&) noexcept(is_nothrow_deinit{});

                /// @brief Deinitializes the stored handle and sets stored
                /// handle to `null_handle`.
                void reset() noexcept(is_nothrow_deinit{});

                /// @brief Deinitializes the stored handle and sets stored
                /// handle to `handle`.
                void reset(const handle_type& handle) noexcept(
                    is_nothrow_deinit{});

                /// @brief Swaps the stored handles and ref counters of `*this`
                /// and `rhs`.
                void swap(shared& rhs) noexcept;

                /// @brief Returns the number of different `shared` instances
                /// managing the current handle.
                /// @details `*this` is included in the count. If a null handle
                /// is being stored, `0` is returned.
                auto use_count() const noexcept;

                /// @brief Returns `true` if `*this` is the only instance
                /// managing the stored handle.
                /// @details Equivalent to `use_count() == 1`.
                bool unique() const noexcept;

                /// @brief Returns `true` if both `lhs` and `rhs` store the same
                /// handle.
                template <typename>
                friend bool operator==(
                    const shared& lhs, const shared& rhs) noexcept;

                /// @brief Returns `true` if `lhs` and `rhs` store different
                /// handles.
                template <typename>
                friend bool operator!=(
                    const shared& lhs, const shared& rhs) noexcept;

                template <typename>
                friend void swap(shared& lhs, shared& rhs) noexcept;
            };
        } // namespace impl

        template <typename TBehavior>
        using shared = impl::shared<TBehavior, impl::shared_lock_policy::none>;
    } // namespace resource
} // namespace vrm::core
