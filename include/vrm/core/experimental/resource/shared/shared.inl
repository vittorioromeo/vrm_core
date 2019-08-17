// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include "./metadata.hpp"
#include "./policies.hpp"
#include "./ref_counter.hpp"
#include "./shared.hpp"
#include <vrm/core/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/fwd.hpp>

namespace vrm::core
{
    namespace resource
    {
        namespace impl
        {
            template <typename TBehavior, typename TLockPolicy>
                VRM_CORE_ALWAYS_INLINE auto& VRM_CORE_CONST_FN
                shared<TBehavior, TLockPolicy>::access_ref_counter() &
                noexcept
            {
                // TODO: use lock policy
                return _ref_counter;
            }

            template <typename TBehavior, typename TLockPolicy>
            VRM_CORE_ALWAYS_INLINE const auto& VRM_CORE_CONST_FN
            shared<TBehavior, TLockPolicy>::access_ref_counter() const& noexcept
            {
                return _ref_counter;
            }

            template <typename TBehavior, typename TLockPolicy>
                VRM_CORE_ALWAYS_INLINE auto
                shared<TBehavior, TLockPolicy>::access_ref_counter() &&
                noexcept
            {
                return std::move(_ref_counter);
            }

            template <typename TBehavior, typename TLockPolicy>
            VRM_CORE_ALWAYS_INLINE void
            shared<TBehavior, TLockPolicy>::nullify_and_assert() noexcept
            {
                base_type::nullify();

                // If the current handle is set to null, the shared resource
                // should not point to any metadata.
                VRM_CORE_ASSERT(base_type::is_null_handle());
                VRM_CORE_ASSERT(access_ref_counter().is_null());
            }

            template <typename TBehavior, typename TLockPolicy>
            void shared<TBehavior, TLockPolicy>::acquire_from_null_if_required()
            {
                if(base_type::is_null_handle()) return;

                // Only acquire if the current handle is valid.
                access_ref_counter().acquire_from_null();
            }

            template <typename TBehavior, typename TLockPolicy>
            void shared<TBehavior, TLockPolicy>::acquire_existing_if_required()
            {
                if(base_type::is_null_handle()) return;

                // Only acquire if the current handle is valid.
                access_ref_counter().acquire_existing();
            }

            template <typename TBehavior, typename TLockPolicy>
            shared<TBehavior, TLockPolicy>::~shared() noexcept
            {
                // Lose ownership upon destruction, if `_ref_counter` is not
                // null.
                reset();
            }

            template <typename TBehavior, typename TLockPolicy>
            shared<TBehavior, TLockPolicy>::shared(const shared& rhs)
                : base_type{rhs._handle}, _ref_counter{rhs.access_ref_counter()}
            {
                // Two construction possibilities:
                // 1. From a non-owning shared pointer (null handle).
                // 2. From an owning shared pointer.

                // There is no way we need to allocate new metadata.
                // We either need to do nothing, or increment an existing
                // metadata
                // ownership counter.
                acquire_existing_if_required();
            }

            template <typename TBehavior, typename TLockPolicy>
            auto& shared<TBehavior, TLockPolicy>::operator=(const shared& rhs)
            {
                // Prevent self-assignment.
                VRM_CORE_ASSERT(this != &rhs);

                // Update handle and ref counter.
                base_type::_handle = rhs._handle;
                _ref_counter = rhs.access_ref_counter();

                // If `rhs`'s handle was null, do nothing - otherwise increment
                // the metadata ownership counter.
                acquire_existing_if_required();

                return *this;
            }

            template <typename TBehavior, typename TLockPolicy>
            shared<TBehavior, TLockPolicy>::shared(
                const handle_type& handle) noexcept
                : base_type{handle}
            {
                // If `handle` is not null, we need to allocate metadata.
                acquire_from_null_if_required();
            }

            template <typename TBehavior, typename TLockPolicy>
            shared<TBehavior, TLockPolicy>::shared(
                const weak_type& rhs) noexcept
                : base_type{rhs._handle}, _ref_counter{rhs._ref_counter}
            {
                // If `handle` is not null, we need to increment the shared
                // ownership counter.
                acquire_existing_if_required();
            }

            template <typename TBehavior, typename TLockPolicy>
            shared<TBehavior, TLockPolicy>::shared(shared&& rhs) noexcept
                : base_type{rhs._handle}, _ref_counter{std::move(
                                              rhs.access_ref_counter())}
            {
                rhs.nullify_and_assert();
            }

            template <typename TBehavior, typename TLockPolicy>
            auto& shared<TBehavior, TLockPolicy>::operator=(shared&& rhs) // .
                noexcept(is_nothrow_deinit{})
            {
                VRM_CORE_ASSERT(this != &rhs);

                if(!base_type::is_null_handle())
                {
                    lose_ownership();
                }

                base_type::_handle = std::move(rhs._handle);
                _ref_counter = std::move(rhs.access_ref_counter());

                rhs.nullify_and_assert();
                return *this;
            }

            template <typename TBehavior, typename TLockPolicy>
            void shared<TBehavior, TLockPolicy>::lose_ownership() // .
                noexcept(is_nothrow_deinit{})
            {
                // Assumes and asserts there is a valid metadata allocated.

                // Decrement the ownership count from the metadata.
                // If the count reaches zero, the resource will be
                // deinitialized.
                // The `ref_counter` internal metadata pointer is set to
                // `nullptr`.
                access_ref_counter().lose_ownership(
                    [this] { base_type::deinit(); });

                // Sets the current handle to null, and asserts that
                // `ref_counter`
                // is null as well, since we're not owning anything.
                nullify_and_assert();
            }

            template <typename TBehavior, typename TLockPolicy>
            void shared<TBehavior, TLockPolicy>::reset() // .
                noexcept(is_nothrow_deinit{})
            {
                // Check if a valid metadata instance exists.
                if(access_ref_counter().is_null())
                {
                    // If no metadata instance has been allocated, we simply
                    // make sure that we're not the owner of any handle.
                    VRM_CORE_ASSERT(base_type::is_null_handle());
                }
                else
                {
                    // Otherwise, we lose ownership of the current handle.
                    lose_ownership();
                }
            }

            template <typename TBehavior, typename TLockPolicy>
            void shared<TBehavior, TLockPolicy>::reset(
                const handle_type& handle) // .
                noexcept(is_nothrow_deinit{})
            {
                // Checks if we're owning any non-null handle.
                if(base_type::is_null_handle())
                {
                    // If we don't own anything (`null_handle`), then
                    // we set the current handle to `handle`...
                    base_type::_handle = handle;

                    // ...and we call `acquire_from_null`, which allocates
                    // a new metadata instance on the heap, setting its
                    // ownership counter to one.
                    access_ref_counter().acquire_from_null();
                }
                else
                {
                    // If we're currently the owner of an handle, we
                    // must lose ownership before owning another handle.
                    lose_ownership();

                    // Set the current handle to `handle`.
                    base_type::_handle = handle;

                    // If the new handle is not null, we need to allocate
                    // metadata.
                    acquire_from_null_if_required();
                }
            }

            template <typename TBehavior, typename TLockPolicy>
            void shared<TBehavior, TLockPolicy>::swap(shared& rhs) noexcept
            {
                using std::swap;
                base_type::swap(rhs);

                // TODO: access?
                swap(_ref_counter, rhs._ref_counter);
            }


            template <typename TBehavior, typename TLockPolicy>
            auto shared<TBehavior, TLockPolicy>::use_count() const noexcept
            {
                return access_ref_counter().use_count();
            }

            template <typename TBehavior, typename TLockPolicy>
            bool shared<TBehavior, TLockPolicy>::unique() const noexcept
            {
                return use_count() == 1;
            }

            template <typename TBehavior, typename TLockPolicy>
            bool operator==(const shared<TBehavior, TLockPolicy>& lhs,
                const shared<TBehavior, TLockPolicy>& rhs) noexcept
            {
                return lhs.get() == rhs.get();
            }

            template <typename TBehavior, typename TLockPolicy>
            bool operator!=(const shared<TBehavior, TLockPolicy>& lhs,
                const shared<TBehavior, TLockPolicy>& rhs) noexcept
            {
                return !(lhs == rhs);
            }

            template <typename TBehavior, typename TLockPolicy>
            void swap(shared<TBehavior, TLockPolicy>& lhs,
                shared<TBehavior, TLockPolicy>& rhs) noexcept
            {
                lhs.swap(rhs);
            }
        } // namespace impl
    }     // namespace resource
} // namespace vrm::core
