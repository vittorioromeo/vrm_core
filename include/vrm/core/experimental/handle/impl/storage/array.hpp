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

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        namespace storage
        {
            // Fixed array, uses ptrs as metadata refs
            template <typename TSettings, sz_t TCount>
            class hs_array
            {
            public:
                using settings_type = TSettings;
                using target_type = impl::target_type<settings_type>;
                using counter_type = impl::counter_type<settings_type>;
                using metadata_type = impl::metadata_type<settings_type>;
                using metadata_ref_type = metadata_type*;

                using handle_type =
                    impl::handle_type<settings_type, metadata_ref_type>;

                static constexpr sz_t count{TCount};

            private:
                std::array<metadata_type, count> _metadata;
                metadata_ref_type _next_ref{_metadata.data()};

            public:
                auto& metadata_from_handle(const handle_type& h) noexcept
                {
                    return *(h._metadata_ref);
                }

                const auto& metadata_from_handle(const handle_type& h) const
                    noexcept
                {
                    return *(h._metadata_ref);
                }

                auto create(const target_type& target)
                {
                    // Out of the array.
                    VRM_CORE_ASSERT_OP(_next_ref, !=, _metadata.data() + count);

                    // Get ptr and increment next ptr.
                    auto m_ref(_next_ref++);

                    // Set it to desired target.
                    m_ref->_target = target;

                    // Return handle.
                    return handle_type{m_ref, m_ref->_counter};
                }

                // TODO:
                template <typename TF>
                void destroy(const handle_type& h, TF&& f)
                {
                    // Get corresponding metadata and invalidate it.
                    auto& m(metadata_from_handle(h));
                    ++(m._counter);

                    // Get last metadata.
                    auto last_m_ref(_next_ref - 1);

                    // Call target cleanup function. (TODO: ?)
                    f(m._target);

                    // Swap indices and `pop_back` (TODO:)
                    std::swap(m._target, last_m_ref->_target);
                    --_next_ref;
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
