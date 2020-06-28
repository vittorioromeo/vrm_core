// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <vrm/core/experimental/handle2/context.hpp>
#include <vrm/core/experimental/handle2/manager/packed_array/packed_array.hpp>
#include <vrm/core/experimental/handle2/settings.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

namespace vrm::core
{
    namespace handle2
    {
        namespace manager
        {
            template <typename TSettings, sz_t TCapacity>
            packed_array<TSettings, TCapacity>::packed_array()
            {
                for(sz_t i(0); i < capacity; ++i)
                {
                    _metadata[i]._target_idx = i;
                    _metadata[i]._counter = 0;
                }
            }

            template <typename TSettings, sz_t TCapacity>
            auto packed_array<TSettings, TCapacity>::create_handle() noexcept
            {
                // Check if we have reached maximum capacity.
                VRM_CORE_ASSERT_OP(_next_ref, <, capacity);

                // Get next valid metadata index and post-increment it.
                VRM_CORE_ASSERT(valid_hd(_next_ref));
                auto m_ref(_next_ref++);

                // Return a new handle.
                return this->create_handle_from_data(m_ref);
            }

            template <typename TSettings, sz_t TCapacity>
            template <typename TF>
            void packed_array<TSettings, TCapacity>::destroy_handle(
                const handle_type& h, TF&& f)
            {
                // Get corresponding metadata and invalidate it.
                auto& m(_metadata[h._data]);
                ++(m._counter);

                // Get last valid metadata.
                auto last_m_ref(_next_ref - 1);

                // Alias the indices of the current and last valid metadata.
                auto& i0(m._target_idx);
                auto& i1(_metadata[last_m_ref]._target_idx);

                // Swap both target indices and target data.
                f(i0, i1);
                using std::swap;
                swap(i0, i1);

                // Decrement next valid metadata index.
                --_next_ref;
            }

            template <typename TSettings, sz_t TCapacity>
            void packed_array<TSettings, TCapacity>::clear_metadata() noexcept
            {
                // Invalidate all existing handles.
                for(sz_t i(0); i < capacity; ++i)
                {
                    _metadata[i]._target_idx = i;
                    ++(_metadata[i]._counter);
                }

                // Reset next valid metadata index.
                _next_ref = 0;
            }
        } // namespace manager
    }     // namespace handle2
} // namespace vrm::core
