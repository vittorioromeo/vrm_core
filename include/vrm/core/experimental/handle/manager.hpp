// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/impl/storage.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        template <typename TStorage>
        class manager
        {
        public:
            using storage_type = TStorage;
            using target_type = impl::target_type<storage_type>;
            using counter_type = impl::counter_type<storage_type>;
            using metadata_type = impl::metadata_type<storage_type>;
            using metadata_ref_type = impl::metadata_ref_type<storage_type>;
            using handle_type = typename storage_type::handle_type;

        private:
            storage_type _storage;

        public:
            VRM_CORE_ALWAYS_INLINE auto valid_handle(const handle_type& h) const
                noexcept
            {
                return h._counter == _storage.metadata_from_handle(h)._counter;
            }

            auto create(const target_type& target)
            {
                auto h(_storage.create(target));
                VRM_CORE_ASSERT(valid_handle(h));
                return h;
            }

            // TODO:
            template <typename TF>
            void destroy(const handle_type& h, TF&& f)
            {
                VRM_CORE_ASSERT(valid_handle(h));
                _storage.destroy(h, FWD(f));
                VRM_CORE_ASSERT(!valid_handle(h));
            }

            // TODO: clear/reserve
        };
    }
}
VRM_CORE_NAMESPACE_END
