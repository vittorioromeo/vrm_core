// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/strategy/storage.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

namespace vrm::core
{
    namespace handle
    {
        namespace impl
        {
            template <typename TSettings>
            using default_allocator =
                std::allocator<strategy::storage_metadata_type<TSettings>>;
        }

        namespace storage
        {
            /// @brief Dynamic (auto-resizing) storage class.
            /// @details Uses indices to point to metadata instances, as the
            /// underlying storage can be reallocated during use.
            template < // .
                typename TSettings,
                typename TAllocator = impl::default_allocator<TSettings> // .
                >
            class hs_vector
            {
            public:
                using settings_type = TSettings;
                using target_type = impl::target_type<settings_type>;
                using counter_type = impl::counter_type<settings_type>;

                using metadata_type =
                    strategy::storage_metadata_type<settings_type>;

                using metadata_ref_type = sz_t;

                using handle_type =
                    impl::handle_type<settings_type, metadata_ref_type>;

                using allocator_type = TAllocator;
                using allocator_traits =
                    ::std::allocator_traits<allocator_type>;

            private:
                std::vector<metadata_type, allocator_type> _metadata;
                metadata_ref_type _next_ref{0};

                void assert_validity(const handle_type& h) const noexcept;
                void grow_if_needed();

            public:
                auto& metadata_from_handle(const handle_type& h) noexcept;

                const auto& metadata_from_handle(const handle_type& h) const
                    noexcept;

                auto create(const target_type& target);
                void invalidate(const handle_type& h) noexcept;

                template <typename TF>
                void destroy(const handle_type& h, TF&& f);

                void clear() noexcept;
                void reserve(sz_t n);
            };
        } // namespace storage
    }     // namespace handle
} // namespace vrm::core
