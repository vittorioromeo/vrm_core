// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <vrm/core/experimental/handle2/container/owning_packed_array/owning_packed_array.hpp>
#include <vrm/core/experimental/handle2/context.hpp>
#include <vrm/core/experimental/handle2/settings.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

namespace vrm::core
{
    namespace handle2
    {
        namespace container
        {
            template <typename TSettings, sz_t TCapacity>
            template <typename TTargetFwd>
            auto owning_packed_array<TSettings, TCapacity>::create(
                TTargetFwd&& t) noexcept
            {
                // Create new valid handle.
                auto h(this->create_handle());

                // Get handle data.
                auto m_ref(h._data);

                // Assign the target to the location pointed by the free
                // metadata.
                this->target(m_ref) = FWD(t);

                // Return the handle.
                return h;
            }

            template <typename TSettings, sz_t TCapacity>
            void owning_packed_array<TSettings, TCapacity>::destroy(
                const handle_type& h)
            {
                // Invalidate metadata for handle `h`.
                // Swap the last valid target with the destroyed one to maintain
                // array packedness.
                this->destroy_handle(
                    h, [this](auto invalid_index, auto valid_index) {
                        using std::swap;
                        swap(_targets[invalid_index], _targets[valid_index]);
                    });
            }

            template <typename TSettings, sz_t TCapacity>
            void owning_packed_array<TSettings, TCapacity>::clear() noexcept
            {
                this->clear_metadata();
            }
        } // namespace container
    }     // namespace handle2
} // namespace vrm::core
