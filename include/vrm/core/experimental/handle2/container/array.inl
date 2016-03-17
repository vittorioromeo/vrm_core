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
        namespace container
        {
            template <typename TSettings, sz_t TCapacity>
            array<TSettings, TCapacity>::array()
            {
                for(sz_t i(0); i < capacity; ++i)
                {
                    _targets[i] = 99;
                    _metadata[i]._target_idx = i;
                    _metadata[i]._counter = 0;
                }
            }

            template <typename TSettings, sz_t TCapacity>
            template <typename TTargetFwd>
            auto array<TSettings, TCapacity>::create(TTargetFwd&& t) noexcept
            {
                // Out of the array.
                VRM_CORE_ASSERT_OP(_next_ref, <, capacity);

                // Get ptr and increment next ptr.
                VRM_CORE_ASSERT(valid_hd(_next_ref));
                auto m_ref(_next_ref++);

                // Set it to desired target.
                target(m_ref) = FWD(t);

                // Return handle.
                return handle_type{m_ref, counter(m_ref)};
            }

            template <typename TSettings, sz_t TCapacity>
            void array<TSettings, TCapacity>::destroy(const handle_type& h)
            {
                // Get corresponding metadata and invalidate it.
                auto& m(_metadata[h._data]);
                ++(m._counter);

                // Get last metadata.
                auto last_m_ref(_next_ref - 1);

                // Swap indices and `pop_back`.
                auto& i0(m._target_idx);
                auto& i1(_metadata[last_m_ref]._target_idx);

                std::swap(_targets[i0], _targets[i1]);
                std::swap(i0, i1);
                --_next_ref;
            }

            template <typename TSettings, sz_t TCapacity>
            void array<TSettings, TCapacity>::clear() noexcept
            {
                // Invalidate all existing handles.
                for(sz_t i(0); i < capacity; ++i)
                {
                    _metadata[i]._target_idx = i;
                    ++(_metadata[i]._counter);
                }

                _next_ref = 0;
            }
        }
    }
}
VRM_CORE_NAMESPACE_END
