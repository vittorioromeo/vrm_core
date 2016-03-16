// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/impl/storage.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        namespace strategy
        {
            template <                     // .
                typename TMetadataRefType, // .
                typename TTargetGetter,    // .
                typename TCounterGetter    // .
                >
            class custom_getters
            {
            public:
                using metadata_ref_type = TMetadataRefType;
                using target_getter_type = TTargetGetter;
                using counter_getter_type = TCounterGetter;

            private:
                target_getter_type _target_getter;
                counter_getter_type _counter_getter;

            public:
                template <typename TFwdTG, typename TFwdCG>
                custom_getters(TFwdTG&& tg, TFwdCG&& cg)
                    : _target_getter{FWD(tg)}, _counter_getter{FWD(cg)}
                {
                }

                auto& target(const metadata_ref_type& mr)
                {
                    return _target_getter(mr);
                }
                const auto& target(const metadata_ref_type& mr) const
                {
                    return _target_getter(mr);
                }

                auto& counter(const metadata_ref_type& mr)
                {
                    return _counter_getter(mr);
                }
                const auto& counter(const metadata_ref_type& mr) const
                {
                    return _counter_getter(mr);
                }
            };

            template <                  // .
                typename TSettings,     // .
                typename TMetadataRef,  // .
                typename TCustomGetters // .
                >
            class custom
            {
            public:
                using settings_type = TSettings;
                using metadata_ref_type = TMetadataRef;
                using custom_getters_type = TCustomGetters;
                using target_type = typename settings_type::target_type;
                using counter_type = typename settings_type::counter_type;

                using handle_type =
                    typename settings_type::template handle_type<
                        metadata_ref_type>;

            private:
                custom_getters_type _custom_getters;
                metadata_ref_type _next_ref{0};

            public:
                template <typename... Ts>
                custom(Ts&&... xs)
                    : _custom_getters(FWD(xs)...)
                {
                }

                auto valid_handle(const handle_type& h) const noexcept
                {
                    // Compare local handle instance counter with storage
                    // counter.
                    return h._counter ==
                           _custom_getters.counter(h._metadata_ref);
                }

                auto invalidate(const handle_type& h) noexcept
                {
                    auto& c(_custom_getters.counter(h._metadata_ref));
                    ++c;
                }

                auto create(const target_type& target)
                {
                    // Get index and increment next index.
                    auto m_ref(_next_ref++);

                    // Set it to desired target.
                    // auto& m(_metadata[m_ref]);
                    auto& m_target(_custom_getters.target(m_ref));
                    m_target = target;

                    // Return handle.
                    return handle_type{m_ref, _custom_getters.counter(m_ref)};
                }

                template <typename TF>
                void destroy(const handle_type& h, TF&& f)
                {
                    // Get corresponding metadata and invalidate it.
                    // auto& m(metadata_from_handle(h));
                    auto& metadata_target(
                        _custom_getters.target(h._metadata_ref));

                    auto& metadata_counter(
                        _custom_getters.counter(h._metadata_ref));

                    ++(metadata_counter);

                    // Get last metadata.
                    auto& last_m_target(_custom_getters.target(_next_ref - 1));

                    // Call target cleanup function. (TODO: ?)
                    f(metadata_target);

                    // Swap indices and `pop_back` (TODO:)
                    std::swap(metadata_target, last_m_target);
                    --_next_ref;
                }

                void clear()
                {
                    _next_ref = 0;
                }

                void reserve(sz_t)
                {
                }

                auto& access(const handle_type& h)
                {
                    return _custom_getters.target(h._metadata_ref);
                }
                const auto& access(const handle_type& h) const
                {
                    return _custom_getters.target(h._metadata_ref);
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
