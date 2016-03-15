// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/impl/storage.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        namespace strategy
        {
            template <typename TSettings>
            struct storage_metadata_type
            {
                using settings_type = TSettings;
                using target_type = typename settings_type::target_type;
                using counter_type = typename settings_type::counter_type;

                target_type _target;
                counter_type _counter{0};
            };

            template <typename TSettings, typename TStorage>
            class storage
            {
            public:
                using settings_type = TSettings;
                using storage_type = TStorage;
                using target_type = typename settings_type::target_type;
                using counter_type = typename settings_type::counter_type;

                using metadata_type = storage_metadata_type<TSettings>;

                using metadata_ref_type =
                    typename storage_type::metadata_ref_type;

                using handle_type =
                    typename settings_type::template handle_type<
                        metadata_ref_type>;

            private:
                storage_type _storage;

            public:
                auto valid_handle(const handle_type& h) const noexcept
                {
                    // Compare local handle instance counter with storage
                    // counter.
                    return h._counter ==
                           _storage.metadata_from_handle(h)._counter;
                }

                auto create(const target_type& target)
                {
                    return _storage.create(target);
                }

                template <typename TF>
                void destroy(const handle_type& h, TF&& f)
                {
                    _storage.destroy(h, FWD(f));
                }

                void clear()
                {
                    _storage.clear();
                }

                void reserve(sz_t n)
                {
                    _storage.reserve(n);
                }

                auto& access(const handle_type& h)
                {
                    return _storage.metadata_from_handle(h)._target;
                }

                const auto& access(const handle_type& h) const
                {
                    return _storage.metadata_from_handle(h)._target;
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
