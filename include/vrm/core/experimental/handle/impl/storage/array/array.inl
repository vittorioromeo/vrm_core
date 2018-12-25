// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/impl/storage/array/array.hpp>

namespace vrm::core
{
    namespace handle
    {
        namespace storage
        {
            template <typename TSettings, sz_t TCount>
            auto& hs_array<TSettings, TCount>::metadata_from_handle(
                const handle_type& h) noexcept
            {
                return *(h._metadata_ref);
            }

            template <typename TSettings, sz_t TCount>
            const auto& hs_array<TSettings, TCount>::metadata_from_handle(
                const handle_type& h) const noexcept
            {
                return *(h._metadata_ref);
            }

            template <typename TSettings, sz_t TCount>
            auto hs_array<TSettings, TCount>::create(
                const target_type& target) noexcept
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

            template <typename TSettings, sz_t TCount>
            void hs_array<TSettings, TCount>::invalidate(
                const handle_type& h) noexcept
            {
                auto& m(metadata_from_handle(h));
                ++(m._counter);
            }

            template <typename TSettings, sz_t TCount>
            template <typename TF>
            void hs_array<TSettings, TCount>::destroy(
                const handle_type& h, TF&& f)
            {
                // Get corresponding metadata and invalidate it.
                auto& m(metadata_from_handle(h));
                invalidate(h);

                // Get last metadata.
                auto last_m_ref(_next_ref - 1);

                // Call target cleanup function. (TODO: ?)
                f(m._target);

                // Swap indices and `pop_back` (TODO:)
                using std::swap;
                swap(m._target, last_m_ref->_target);
                --_next_ref;
            }

            template <typename TSettings, sz_t TCount>
            void hs_array<TSettings, TCount>::clear() noexcept
            {
                // Invalidate all existing handles.
                for(auto& m : _metadata)
                {
                    ++(m._counter);
                }

                _next_ref = _metadata.data();
            }

            template <typename TSettings, sz_t TCount>
            void hs_array<TSettings, TCount>::reserve(sz_t) noexcept
            {
            }
        }
    }
}
