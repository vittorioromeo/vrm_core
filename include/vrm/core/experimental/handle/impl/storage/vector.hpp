// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        namespace impl
        {
            template <typename TSettings>
            using default_allocator = std::allocator<metadata_type<TSettings>>;
        }

        namespace storage
        {
            // Resizable array, uses idxs as metadata refs
            template <typename TSettings,
                typename TAllocator = impl::default_allocator<TSettings>>
            class hs_vector
            {
            public:
                using settings_type = TSettings;
                using target_type = impl::target_type<settings_type>;
                using counter_type = impl::counter_type<settings_type>;
                using metadata_type = impl::metadata_type<settings_type>;
                using metadata_ref_type = sz_t;

                using handle_type =
                    impl::handle_type<settings_type, metadata_ref_type>;

                using allocator_type = TAllocator;
                using allocator_traits =
                    ::std::allocator_traits<allocator_type>;

            private:
                std::vector<metadata_type, allocator_type> _metadata;
                metadata_ref_type _next_ref{0};

                void assert_validity(const handle_type& h) const noexcept
                {
                    VRM_CORE_ASSERT_OP(h._metadata_ref, >=, 0);
                    VRM_CORE_ASSERT_OP(h._metadata_ref, <, _metadata.size());
                }

                void grow_if_needed()
                {
                    if(_next_ref < _metadata.size()) return;
                    _metadata.resize(_metadata.size() + 100);
                }

            public:
                auto& metadata_from_handle(const handle_type& h) noexcept
                {
                    assert_validity(h);
                    return _metadata[h._metadata_ref];
                }

                const auto& metadata_from_handle(const handle_type& h) const
                    noexcept
                {
                    assert_validity(h);
                    return _metadata[h._metadata_ref];
                }

                auto create(const target_type& target)
                {
                    grow_if_needed();

                    // Get index and increment next index.
                    auto m_ref(_next_ref++);

                    // Set it to desired target.
                    auto& m(_metadata[m_ref]);
                    m._target = target;

                    // Return handle.
                    return handle_type{m_ref, m._counter};
                }

                template <typename TF>
                void destroy(const handle_type& h, TF&& f)
                {
                    // Get corresponding metadata and invalidate it.
                    auto& m(metadata_from_handle(h));
                    ++(m._counter);

                    // Get last metadata.
                    auto& last_m(_metadata[_next_ref - 1]);

                    // Call target cleanup function. (TODO: ?)
                    f(m._target);

                    // Swap indices and `pop_back` (TODO:)
                    std::swap(m._target, last_m._target);
                    --_next_ref;
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
