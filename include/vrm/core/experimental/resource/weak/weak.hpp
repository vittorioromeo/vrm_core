// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/shared.hpp>

namespace vrm::core::resource::impl
{
    // TODO:
    template <typename TBehavior, typename TLockPolicy>
    class weak
    {
        template <typename, typename>
        friend class shared;

    public:
        using behavior_type = TBehavior;
        using handle_type = typename behavior_type::handle_type;
        using ref_counter_type = impl::shared_ref_counter;
        using lock_policy_type = TLockPolicy;
        using shared_type = shared<TBehavior, TLockPolicy>;

    private:
        handle_type _handle{behavior_type::null_handle()};
        ref_counter_type _ref_counter;

    public:
        /// @brief Manages a null handle.
        /// @details `expired()` will return `true`.
        constexpr weak() noexcept;

        /// @brief Manages `rhs`'s handle.
        weak(const weak &rhs) noexcept;

        /// @brief Manages `rhs`'s handle.
        weak(const shared_type &rhs) noexcept;

        /// @brief Manages `rhs`'s handle. `rhs` will stop managing its
        /// handle.
        weak(weak &&rhs) noexcept;

        /// @brief Manages `rhs`'s handle.
        auto &operator=(const weak &rhs) noexcept;

        /// @brief Manages `rhs`'s handle.
        auto &operator=(const shared_type &rhs) noexcept;

        /// @brief Manages `rhs`'s handle. `rhs` will stop managing its
        /// handle.
        auto &operator=(weak &&rhs) noexcept;

        /// @brief Destroys the weak resource.
        /// @details Has no effect on the managed object.
        ~weak();

        /// @brief Swaps the stored handles and ref counters of `*this`
        /// and `rhs`.
        void swap(weak &rhs) noexcept;

        /// @brief Releases the current handle.
        /// @details `expired()` will return `true`. Has no effect on
        /// the managed object.
        void reset() noexcept;

        /// @brief Returns the number of shared resources managing the
        /// stored handle.
        [[nodiscard]] auto use_count() const noexcept;

        /// @brief Returns `true` if the managed object has already been
        /// deleted.
        /// @details Equivalent to `use_count() == 0`.
        [[nodiscard]] auto expired() const noexcept;

        /// @brief Creates a shared resource that shares ownership of
        /// the managed object.
        /// @details If the stored handle is null, a null shared
        /// resource is returned.
        [[nodiscard]] auto lock() const noexcept;

        template <typename>
        friend void swap(weak &lhs, weak &rhs) noexcept;
    };
} // namespace vrm::core::resource::impl
