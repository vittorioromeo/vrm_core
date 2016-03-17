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
            class array : public context<TSettings, array<TSettings, TCapacity>>
            {
            public:
                using target_type = aliases::target_type<TSettings>;
                using counter_type = aliases::counter_type<TSettings>;
                using handle_type = aliases::handle_type<TSettings>;
                using handle_data_type = aliases::handle_data_type<TSettings>;
                static constexpr sz_t capacity{TCapacity};

            private:
                struct metadata_type
                {
                    sz_t _target_idx;
                    counter_type _counter{0};
                };

                using targets_array = std::array<target_type, capacity>;
                using metadata_array = std::array<metadata_type, capacity>;

                targets_array _targets;
                metadata_array _metadata;
                handle_data_type _next_ref{0};

                auto valid_hd(const handle_data_type& hd) const noexcept
                {
                    return hd >= 0 && hd < capacity;
                }

            public:
                array();

                array(const array&) = default;
                array& operator=(const array&) = default;

                array(array&& rhs) = default;
                array& operator=(array&& rhs) = default;

                auto& target(sz_t x)
                {
                    return _targets[_metadata[x]._target_idx];
                }
                const auto& target(sz_t x) const
                {
                    return _targets[_metadata[x]._target_idx];
                }

                auto& counter(sz_t x)
                {
                    return _metadata[x]._counter;
                }
                const auto& counter(sz_t x) const
                {
                    return _metadata[x]._counter;
                }

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

                void print()
                {
                    std::cout << "\n\n";
                    for(auto t : _targets) std::cout << t << "\t";
                    std::cout << "\n";
                    for(auto m : _metadata) std::cout << m._target_idx << "\t";
                    std::cout << "\n";
                    for(auto m : _metadata) std::cout << m._counter << "\t";
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
