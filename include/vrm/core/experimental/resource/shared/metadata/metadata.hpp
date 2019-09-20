// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/assert/assert.hpp>
#include <vrm/core/config.hpp>

namespace vrm::core::resource::impl
{
    // TODO: templatize with policy, use atomics for lock-policy

    /// @brief Type used to count references.
    using shared_counter_type = unsigned int;

    /// @brief Metadata necessary to keep track of owning shared
    /// references and weak references.
    /// @details This instance gets allocated once per resource, and
    /// deallocated when the resource is deinitialized.
    class shared_metadata
    {
    private:
        shared_counter_type _owner_count;
        shared_counter_type _weak_count;

    public:
        shared_metadata(shared_counter_type owner_count,
            shared_counter_type weak_count) noexcept;

        // Prevent copies.
        shared_metadata(const shared_metadata &) = delete;
        shared_metadata &operator=(const shared_metadata &) = delete;

        // Prevent moves.
        shared_metadata(shared_metadata &&) = delete;
        shared_metadata &operator=(shared_metadata &&) = delete;

        void increment_owner() noexcept;
        void decrement_owner() noexcept;

        void increment_weak() noexcept;
        void decrement_weak() noexcept;

        [[nodiscard]] auto owner_count() const noexcept;
        [[nodiscard]] auto weak_count() const noexcept;
        [[nodiscard]] auto total_count() const noexcept;

        [[nodiscard]] auto has_any_ref() const noexcept;
    };
} // namespace vrm::core::resource::impl
