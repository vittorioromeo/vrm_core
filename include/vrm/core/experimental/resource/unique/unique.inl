// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/resource/base.hpp>
#include <vrm/core/experimental/resource/unique/unique.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            template <typename TBehavior>
            unique<TBehavior>::~unique() noexcept
            {
                // Release ownership of the stored handle, deinitializing it.
                // The behavior must handle $null_handle$ deinitialization.
                reset();
            }

            template <typename TBehavior>
            unique<TBehavior>::unique(const handle_type& handle) noexcept
                : base_type{handle}
            {
            }

            template <typename TBehavior>
            unique<TBehavior>::unique(unique&& rhs) noexcept
                : base_type{rhs.release()}
            {
            }

            template <typename TBehavior>
            auto& unique<TBehavior>::operator=(unique&& rhs) noexcept
            {
                // Avoid self-assignment.
                VRM_CORE_ASSERT(this != &rhs);

                // $rhs$ releases his handle, becoming a $null_handle$ holder.
                // We take ownership of his previous handle.
                reset(rhs.release());
                return *this;
            }

            template <typename TBehavior>
            auto unique<TBehavior>::release() noexcept
            {
                // Release ownership of the current handle, returning it.
                // Sets the current handle to $null_handle$.
                return base_type::release_and_nullify();
            }

            template <typename TBehavior>
            void unique<TBehavior>::reset() noexcept
            {
                // Call the behavior's $deinit$ static method.
                // The behavior must handle $null_handle$ deinitialization.
                base_type::deinit();

                // Sets the stored handle to $null_handle$.
                base_type::nullify();
            }

            template <typename TBehavior>
            void unique<TBehavior>::reset(const handle_type& handle) noexcept
            {
                // Call the behavior's $deinit$ static method.
                // The behavior must handle $null_handle$ deinitialization.
                base_type::deinit();

                // Sets the stored handle to $handle$.
                base_type::_handle = handle;
            }

            template <typename TBehavior>
            void unique<TBehavior>::swap(unique& rhs) noexcept
            {
                base_type::swap(rhs);
            }

            template <typename TBehavior>
            bool operator==(const unique<TBehavior>& lhs,
                const unique<TBehavior>& rhs) noexcept
            {
                return lhs._handle == rhs._handle;
            }

            template <typename TBehavior>
            bool operator!=(const unique<TBehavior>& lhs,
                const unique<TBehavior>& rhs) noexcept
            {
                return !(lhs == rhs);
            }

            template <typename TBehavior>
            void swap(unique<TBehavior>& lhs, unique<TBehavior>& rhs) noexcept
            {
                lhs.swap(rhs);
            }
        }
    }
}
VRM_CORE_NAMESPACE_END
