// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/impl/storage.hpp>
#include <vrm/core/experimental/handle/manager/manager.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        template <typename TStorage>
        VRM_CORE_ALWAYS_INLINE auto manager<TStorage>::valid_handle(
            const handle_type& h) const noexcept
        {
            // Compare local handle instance counter with storage counter.
            return h._counter == _storage.metadata_from_handle(h)._counter;
        }

        template <typename TStorage>
        auto manager<TStorage>::create(const target_type& target) // .
            noexcept(noexcept(_storage.create(target)))
        {
            auto h(_storage.create(target));
            VRM_CORE_ASSERT(valid_handle(h));
            return h;
        }

        // TODO:
        template <typename TStorage>
        template <typename TF>
        void manager<TStorage>::destroy(const handle_type& h, TF&& f) // .
            noexcept(noexcept((_storage.destroy(h, f))))
        {
            VRM_CORE_ASSERT(valid_handle(h));
            _storage.destroy(h, FWD(f));
            VRM_CORE_ASSERT(!valid_handle(h));
        }

        template <typename TStorage>
        void manager<TStorage>::clear() // .
            noexcept(noexcept(_storage.clear()))
        {
            _storage.clear();
        }

        template <typename TStorage>
        void manager<TStorage>::reserve(sz_t n) // .
            noexcept(noexcept(_storage.reserve(sz_t{})))
        {
            _storage.reserve(n);
        }

        template <typename TStorage>
        auto& manager<TStorage>::access(const handle_type& h) noexcept
        {
            VRM_CORE_ASSERT(valid_handle(h));
            return _storage.metadata_from_handle(h)._target;
        }

        template <typename TStorage>
        const auto& manager<TStorage>::access(const handle_type& h) const
            noexcept
        {
            VRM_CORE_ASSERT(valid_handle(h));
            return _storage.metadata_from_handle(h)._target;
        }
    }
}
VRM_CORE_NAMESPACE_END
