// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/impl/aliases.hpp>
#include <vrm/core/experimental/handle/impl/storage.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
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
