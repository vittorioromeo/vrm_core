// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <utility>
#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/base/base.hpp>

namespace vrm::core
{
    namespace resource
    {
        namespace impl
        {
            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE auto VRM_CORE_CONST_FN
            base<TBehavior>::null_handle() noexcept
            {
                return behavior_type::null_handle();
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE base<TBehavior>::base() noexcept
                : _handle{null_handle()}
            {
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE base<TBehavior>::base(
                const handle_type& handle) noexcept
                : _handle{handle}
            {
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE auto VRM_CORE_PURE_FN
            base<TBehavior>::is_null_handle() const noexcept
            {
                return _handle == null_handle();
            }

            template <typename TBehavior>
            VRM_CORE_ALWAYS_INLINE void base<TBehavior>::deinit() // .
                noexcept(is_nothrow_deinit_t<TBehavior>{})
            {
                behavior_type::deinit(_handle);
            }

            template <typename TBehavior>
            void base<TBehavior>::nullify() noexcept
            {
                _handle = null_handle();
            }

            template <typename TBehavior>
            auto base<TBehavior>::release_and_nullify() noexcept
            {
                auto temp(_handle);
                nullify();
                return temp;
            }

            template <typename TBehavior>
            void base<TBehavior>::swap(base& rhs) noexcept
            {
                using std::swap;
                swap(_handle, rhs._handle);
            }

            template <typename TBehavior>
            auto VRM_CORE_PURE_FN base<TBehavior>::get() const noexcept
            {
                return _handle;
            }

            template <typename TBehavior>
            base<TBehavior>::operator bool() const noexcept
            {
                return !is_null_handle();
            }
        } // namespace impl
    }     // namespace resource
} // namespace vrm::core
