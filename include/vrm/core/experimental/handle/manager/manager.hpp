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
        // TODO:
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
                // TODO:
                // :: metadata_ref_type -> target_type
                target_getter_type _target_getter;

                // TODO:
                // :: metadata_ref_type -> counter_type
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

            template <                     // .
                typename TSettings,        // .
                typename TMetadataRefType, // .
                typename TCustomGetters    // .
                >
            class custom
            {
            public:
                using settings_type = TSettings;
                using metadata_ref_type = TMetadataRefType;
                using custom_getters_type = TCustomGetters;
                using target_type = typename settings_type::target_type;
                using counter_type = typename settings_type::counter_type;

                using handle_type =
                    typename settings_type::template handle_type<
                        metadata_ref_type>;

            private:
                custom_getters_type _custom_getters;

            public:
                auto create(const target_type& target);

                template <typename TF>
                void destroy(const handle_type& h, TF&& f);

                void clear();

                void reserve(sz_t n);

                auto& access(const handle_type& h);
                const auto& access(const handle_type& h) const;
            };

            template <typename TSettings, typename TStorage>
            class storage
            {
            public:
                using settings_type = TSettings;
                using storage_type = TStorage;
                using target_type = typename settings_type::target_type;
                using counter_type = typename settings_type::counter_type;

                struct metadata_type
                {
                    target_type _target;
                    counter_type _counter{0};
                };

                using metadata_ref_type =
                    typename storage_type::metadata_ref_type;

                using handle_type =
                    typename settings_type::template handle_type<
                        metadata_ref_type>;

            private:
                storage_type _storage;

            public:
                auto create(const target_type& target);

                template <typename TF>
                void destroy(const handle_type& h, TF&& f);

                void clear();

                void reserve(sz_t n);

                auto& access(const handle_type& h);
                const auto& access(const handle_type& h) const;
            };
        }

        /// @brief Context that allows the management of handles.
        template <typename TStorage>
        class manager
        {
        public:
            using storage_type = TStorage;
            using target_type = impl::target_type<storage_type>;
            using counter_type = impl::counter_type<storage_type>;
            using metadata_type = impl::metadata_type<storage_type>;
            using metadata_ref_type = impl::metadata_ref_type<storage_type>;
            using handle_type = typename storage_type::handle_type;

        private:
            storage_type _storage;

        public:
            /// @brief Returns `true` if `h` is a valid handle.
            /// @details `h` is invalid if the object it points to was removed
            /// or replaced.
            VRM_CORE_ALWAYS_INLINE auto valid_handle(const handle_type& h) const
                noexcept;

            /// @brief Creates and returns an handle pointing to `target`.
            auto create(const target_type& target) // .
                noexcept(noexcept(_storage.create(target)));

            /// @brief Destroys `h`'s target and invalidates `h`.
            /// @details Requires a `f` cleanup function that will be called on
            /// `h`'s target before invalidating `h`.
            template <typename TF>
            void destroy(const handle_type& h, TF&& f) // .
                noexcept(noexcept((_storage.destroy(h, f))));

            /// @brief Clears all handles.
            void clear() // .
                noexcept(noexcept(_storage.clear()));

            /// @brief Reserves memory for `n` handles.
            /// @details Has no effect on fixed storage types.
            void reserve(sz_t n) // .
                noexcept(noexcept(_storage.reserve(sz_t{})));

            /// @brief Retrieves the target from an handle.
            auto& access(const handle_type& h) noexcept;

            /// @brief Retrieves the target from an handle. (const version)
            const auto& access(const handle_type& h) const noexcept;
        };
    }
}
VRM_CORE_NAMESPACE_END

// TODO: generalize: make storage optional, use function object to retrieve
// counters and targets
