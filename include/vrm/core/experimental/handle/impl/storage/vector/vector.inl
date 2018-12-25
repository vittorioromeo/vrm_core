// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/impl/storage/vector/vector.hpp>

namespace vrm::core
{
    namespace handle
    {
        namespace storage
        {
            template <typename TSettings, typename TAllocator>
            void hs_vector<TSettings, TAllocator>::assert_validity(
                const handle_type& h) const noexcept
            {
                VRM_CORE_ASSERT_OP(h._metadata_ref, >=, 0);
                VRM_CORE_ASSERT_OP(h._metadata_ref, <, _metadata.size());

                // Suppress unused variable warnings in non-debug builds.
                (void)h;
            }

            template <typename TSettings, typename TAllocator>
            void hs_vector<TSettings, TAllocator>::grow_if_needed()
            {
                if(unlikely(_next_ref >= _metadata.size()))
                {
                    _metadata.resize(_metadata.size() + 100);
                }
            }

            template <typename TSettings, typename TAllocator>
            auto& hs_vector<TSettings, TAllocator>::metadata_from_handle(
                const handle_type& h) noexcept
            {
                assert_validity(h);
                return _metadata[h._metadata_ref];
            }

            template <typename TSettings, typename TAllocator>
            const auto& hs_vector<TSettings, TAllocator>::metadata_from_handle(
                const handle_type& h) const noexcept
            {
                assert_validity(h);
                return _metadata[h._metadata_ref];
            }

            template <typename TSettings, typename TAllocator>
            void hs_vector<TSettings, TAllocator>::invalidate(
                const handle_type& h) noexcept
            {
                auto& m(metadata_from_handle(h));
                ++(m._counter);
            }

            template <typename TSettings, typename TAllocator>
            auto hs_vector<TSettings, TAllocator>::create(
                const target_type& target)
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

            template <typename TSettings, typename TAllocator>
            template <typename TF>
            void hs_vector<TSettings, TAllocator>::destroy(
                const handle_type& h, TF&& f)
            {
                // Get corresponding metadata and invalidate it.
                auto& m(metadata_from_handle(h));
                invalidate(h);

                // Get last metadata.
                auto& last_m(_metadata[_next_ref - 1]);

                // Call target cleanup function. (TODO: ?)
                f(m._target);

                // Swap indices and `pop_back` (TODO:)
                using std::swap;
                swap(m._target, last_m._target);
                --_next_ref;
            }

            template <typename TSettings, typename TAllocator>
            void hs_vector<TSettings, TAllocator>::clear() noexcept
            {
                // Invalidate all existing handles.
                for(auto& m : _metadata)
                {
                    ++(m._counter);
                }

                _next_ref = 0;
            }

            template <typename TSettings, typename TAllocator>
            void hs_vector<TSettings, TAllocator>::reserve(sz_t n)
            {
                _metadata.reserve(n);
            }
        }
    }
}
