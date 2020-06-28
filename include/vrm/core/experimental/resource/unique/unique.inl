// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/base.hpp>
#include <vrm/core/experimental/resource/unique/unique.hpp>

namespace vrm::core
{
    namespace resource
    {
        namespace impl
        {
            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE void unique<TBehavior>::reset() // .
                noexcept(is_nothrow_deinit{})
            {
                // Call the behavior's `deinit` static method.
                // The behavior must handle `null_handle` deinitialization.
                base_type::deinit();

                // Sets the stored handle to `null_handle`.
                base_type::nullify();
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE void unique<TBehavior>::reset(
                const handle_type& handle) // .
                noexcept(is_nothrow_deinit{})
            {
                // Call the behavior's `deinit` static method.
                // The behavior must handle `null_handle` deinitialization.
                base_type::deinit();

                // Sets the stored handle to `handle`.
                base_type::_handle = handle;
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE unique<TBehavior>::~unique() // .
                noexcept(is_nothrow_deinit{})
            {
                // Release ownership of the stored handle, deinitializing it.
                // The behavior must handle `null_handle` deinitialization.
                reset();
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE unique<TBehavior>::unique(
                const handle_type& handle) noexcept
                : base_type{handle}
            {
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE unique<TBehavior>::unique(
                unique&& rhs) noexcept
                : base_type{rhs.release()}
            {
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE auto& unique<TBehavior>::operator=(
                unique&& rhs) // .
                noexcept(is_nothrow_deinit{})
            {
                // Avoid self-assignment.
                VRM_CORE_ASSERT(this != &rhs);

                // `rhs` releases his handle, becoming a `null_handle` holder.
                // We take ownership of his previous handle.
                reset(rhs.release());
                return *this;
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE auto unique<TBehavior>::release() noexcept
            {
                // Release ownership of the current handle, returning it.
                // Sets the current handle to `null_handle`.
                return base_type::release_and_nullify();
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE void unique<TBehavior>::swap(
                unique& rhs) noexcept
            {
                base_type::swap(rhs);
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE bool operator==(const unique<TBehavior>& lhs,
                const unique<TBehavior>& rhs) noexcept
            {
                return lhs.get() == rhs.get();
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE bool operator!=(const unique<TBehavior>& lhs,
                const unique<TBehavior>& rhs) noexcept
            {
                return !(lhs == rhs);
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE void swap(
                unique<TBehavior>& lhs, unique<TBehavior>& rhs) noexcept
            {
                lhs.swap(rhs);
            }
        } // namespace impl
    }     // namespace resource
} // namespace vrm::core
