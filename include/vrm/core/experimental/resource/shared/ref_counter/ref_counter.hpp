// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/assert/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/shared/metadata.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

namespace vrm::core::resource::impl
{
    // TODO: test polymorphism with custom shared_ptr
    class shared_ref_counter
    {
    private:
        shared_metadata* _metadata{nullptr};

        auto &access_metadata() noexcept;
        [[nodiscard]] const auto &access_metadata() const noexcept;

        [[nodiscard]] auto weak_count() const noexcept;
        [[nodiscard]] auto total_count() const noexcept;

        [[nodiscard]] auto has_any_ref() const noexcept;

        void increment_owner() noexcept;
        void decrement_owner() noexcept;

        void deallocate() noexcept;

        template <typename TF>
        void deallocate_if_required(TF &&deleter) noexcept;

        void decrement_weak() noexcept;

    public:
        shared_ref_counter() noexcept = default;

        shared_ref_counter(const shared_ref_counter &) = default;
        shared_ref_counter &operator=(const shared_ref_counter &) = default;

        shared_ref_counter(shared_ref_counter &&rhs) noexcept;
        auto &operator=(shared_ref_counter &&rhs) noexcept;

        [[nodiscard]] bool is_null() const noexcept;

        [[nodiscard]] auto owner_count() const noexcept;
        [[nodiscard]] auto use_count() const noexcept;

        void acquire_from_null();
        void acquire_existing() noexcept;

        void increment_weak() noexcept;

        template <typename TF>
        void lose_ownership(TF &&deleter) noexcept;

        template <typename TF>
        void lose_weak(TF &&deleter);
    };
} // namespace vrm::core::resource::impl
