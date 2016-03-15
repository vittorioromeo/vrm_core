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
        /// @brief Context that allows the management of handles.
        template <typename TStrategy>
        class manager
        {
        public:
            using strategy_type = TStrategy;
            using target_type = typename strategy_type::target_type;
            using counter_type = typename strategy_type::counter_type;
            using metadata_ref_type = typename strategy_type::metadata_ref_type;
            using handle_type = typename strategy_type::handle_type;

        private:
            strategy_type _strategy;

        public:
            template <typename... Ts>
            manager(Ts&&... xs)
                : _strategy(FWD(xs)...)
            {
            }

            /// @brief Returns `true` if `h` is a valid handle.
            /// @details `h` is invalid if the object it points to was removed
            /// or replaced.
            VRM_CORE_ALWAYS_INLINE auto valid_handle(const handle_type& h) const
                noexcept;

            /// @brief Creates and returns an handle pointing to `target`.
            auto create(const target_type& target) // .
                noexcept(noexcept(_strategy.create(target)));

            /// @brief Destroys `h`'s target and invalidates `h`.
            /// @details Requires a `f` cleanup function that will be called on
            /// `h`'s target before invalidating `h`.
            template <typename TF>
            void destroy(const handle_type& h, TF&& f) // .
                noexcept(noexcept((_strategy.destroy(h, f))));

            /// @brief Clears all handles.
            void clear() // .
                noexcept(noexcept(_strategy.clear()));

            /// @brief Reserves memory for `n` handles.
            /// @details Has no effect on fixed storage types.
            void reserve(sz_t n) // .
                noexcept(noexcept(_strategy.reserve(sz_t{})));

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
