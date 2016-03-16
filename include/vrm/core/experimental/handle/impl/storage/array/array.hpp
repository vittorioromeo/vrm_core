// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/strategy/storage.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        namespace storage
        {
            /// @brief Fixed storage class.
            /// @details Uses pointers to point to metadata instances.
            /// Moving/copying the storage can invalidate existing pointers.
            template <typename TSettings, sz_t TCount>
            class hs_array
            {
            public:
                using settings_type = TSettings;
                using target_type = impl::target_type<settings_type>;
                using counter_type = impl::counter_type<settings_type>;

                using metadata_type =
                    strategy::storage_metadata_type<settings_type>;

                using metadata_ref_type = metadata_type*;

                using handle_type =
                    impl::handle_type<settings_type, metadata_ref_type>;

                static constexpr sz_t count{TCount};

            private:
                std::array<metadata_type, count> _metadata;
                metadata_ref_type _next_ref{_metadata.data()};

            public:
                auto& metadata_from_handle(const handle_type& h) noexcept;
                const auto& metadata_from_handle(const handle_type& h) const
                    noexcept;

                auto create(const target_type& target) noexcept;
                void invalidate(const handle_type& h) noexcept;

                template <typename TF>
                void destroy(const handle_type& h, TF&& f);

                void clear() noexcept;
                void reserve(sz_t n) noexcept;
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
