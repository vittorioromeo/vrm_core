// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <utility>
#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/base/base.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            template <typename TBehavior>
            auto base<TBehavior>::null_handle() noexcept
            {
                return behavior_type::null_handle();
            }

            template <typename TBehavior>
            base<TBehavior>::base() noexcept : _handle{null_handle()}
            {
            }

            template <typename TBehavior>
            base<TBehavior>::base(const handle_type& handle) noexcept
                : _handle{handle}
            {
            }

            template <typename TBehavior>
            auto base<TBehavior>::is_null_handle() const noexcept
            {
                return _handle == null_handle();
            }

            template <typename TBehavior>
            void base<TBehavior>::deinit()
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
            auto base<TBehavior>::get() const noexcept
            {
                return _handle;
            }

            template <typename TBehavior>
            base<TBehavior>::operator bool() const noexcept
            {
                return !is_null_handle();
            }
        }
    }
}
VRM_CORE_NAMESPACE_END
