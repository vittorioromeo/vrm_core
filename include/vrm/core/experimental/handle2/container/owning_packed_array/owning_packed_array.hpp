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
#include <vrm/core/experimental/handle2/manager.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle2
    {
        namespace container
        {
            /// @brief Handle container with fixed size that packs its contents.
            /// @details Wraps two `std::array` instances. The targets are
            /// contiguous in memory.
            template <typename TSettings, sz_t TCapacity>
            class owning_packed_array
                : public manager::packed_array<TSettings, TCapacity>
            {
            public:
                using target_type = aliases::target_type<TSettings>;
                using counter_type = aliases::counter_type<TSettings>;
                using handle_type = aliases::handle_type<TSettings>;
                using handle_data_type = aliases::handle_data_type<TSettings>;
                static constexpr sz_t capacity{TCapacity};

            private:
                // Target storage.
                using targets_array = std::array<target_type, capacity>;
                targets_array _targets;

            public:
                owning_packed_array() = default;

                owning_packed_array(const owning_packed_array&) = default;
                owning_packed_array& operator=(
                    const owning_packed_array&) = default;

                owning_packed_array(owning_packed_array&& rhs) = default;
                owning_packed_array& operator=(
                    owning_packed_array&& rhs) = default;

            private:
                auto& target(sz_t x)
                {
                    auto target_idx(this->metadata_at(x)._target_idx);
                    return _targets[target_idx];
                }
                const auto& target(sz_t x) const
                {
                    auto target_idx(this->metadata_at(x)._target_idx);
                    return _targets[target_idx];
                }

            public:
                template <typename TTargetFwd>
                auto create(TTargetFwd&& t) noexcept;

                void destroy(const handle_type& h);
                void clear() noexcept;

                auto& targets() noexcept
                {
                    return _targets;
                }
                const auto& targets() const noexcept
                {
                    return _targets;
                }

                auto& access(const handle_type& h)
                {
                    VRM_CORE_ASSERT(this->valid(h));
                    return target(this->data(h));
                }
                const auto& access(const handle_type& h) const
                {
                    VRM_CORE_ASSERT(this->valid(h));
                    return target(this->data(h));
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
