// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/experimental/handle2/settings.hpp>
#include <vrm/core/experimental/handle2/context.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle2
    {
        namespace manager
        {
            /// @brief Handle manager with fixed size.
            /// @details Wraps an `std::array` that managed metadata.
            template <typename TSettings, sz_t TCapacity>
            class packed_array
                : public context<TSettings, packed_array<TSettings, TCapacity>>
            {
            public:
                using counter_type = aliases::counter_type<TSettings>;
                using handle_type = aliases::handle_type<TSettings>;
                using handle_data_type = aliases::handle_data_type<TSettings>;
                static constexpr sz_t capacity{TCapacity};

            private:
                /// @brief Metadata for a target. Stores the target index and
                /// the validity counter.
                struct metadata_type
                {
                    sz_t _target_idx;
                    counter_type _counter{0};
                };

                // Metadata storage.
                using metadata_array_type = std::array<metadata_type, capacity>;
                metadata_array_type _metadata;

                // Next usable free metadata index.
                handle_data_type _next_ref{0};

                auto valid_hd(const handle_data_type& hd) const noexcept
                {
                    return hd >= 0 && hd < capacity;
                }

            public:
                packed_array();

                packed_array(const packed_array&) = default;
                packed_array& operator=(const packed_array&) = default;

                packed_array(packed_array&& rhs) = default;
                packed_array& operator=(packed_array&& rhs) = default;

            protected:
                auto& metadata_at(sz_t x) noexcept
                {
                    return _metadata[x];
                }
                const auto& metadata_at(sz_t x) const noexcept
                {
                    return _metadata[x];
                }

                auto& counter(sz_t x)
                {
                    return metadata_at(x)._counter;
                }
                const auto& counter(sz_t x) const
                {
                    return metadata_at(x)._counter;
                }

                auto create_handle() noexcept;

                template <typename TF>
                void destroy_handle(const handle_type& h, TF&& f);

                void clear_metadata() noexcept;
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
