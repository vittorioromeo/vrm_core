// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include "./ref_counter.hpp"
#include <vrm/core/assert/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

namespace vrm::core::resource::impl
{
    VRM_CORE_ALWAYS_INLINE auto &VRM_CORE_PURE_FN
    shared_ref_counter::access_metadata() noexcept
    {
        VRM_CORE_ASSERT(!is_null());
        return *_metadata;
    }

    VRM_CORE_ALWAYS_INLINE const auto &VRM_CORE_PURE_FN
    shared_ref_counter::access_metadata() const noexcept
    {
        VRM_CORE_ASSERT(!is_null());
        return *_metadata;
    }

    VRM_CORE_ALWAYS_INLINE auto VRM_CORE_PURE_FN
    shared_ref_counter::weak_count() const noexcept
    {
        return access_metadata().weak_count();
    }

    VRM_CORE_ALWAYS_INLINE auto VRM_CORE_PURE_FN
    shared_ref_counter::total_count() const noexcept
    {
        return access_metadata().total_count();
    }

    VRM_CORE_ALWAYS_INLINE auto VRM_CORE_PURE_FN
    shared_ref_counter::has_any_ref() const noexcept
    {
        return access_metadata().has_any_ref();
    }

    VRM_CORE_ALWAYS_INLINE void shared_ref_counter::increment_owner() noexcept
    {
        access_metadata().increment_owner();
    }

    VRM_CORE_ALWAYS_INLINE void shared_ref_counter::decrement_owner() noexcept
    {
        access_metadata().decrement_owner();
    }

    VRM_CORE_ALWAYS_INLINE void shared_ref_counter::deallocate() noexcept
    {
        // TODO: total_count?
        VRM_CORE_ASSERT_OP(access_metadata().owner_count(), ==, 0);
        delete _metadata;
    }

    template <typename TF>
    void shared_ref_counter::deallocate_if_required(TF &&deleter) noexcept
    {
        if(!has_any_ref())
        {
            deleter();
            deallocate();
        }

        _metadata = nullptr;
    }

    VRM_CORE_ALWAYS_INLINE void shared_ref_counter::decrement_weak() noexcept
    {
        // TODO: weak is never decremented!
        access_metadata().decrement_weak();
    }

    VRM_CORE_ALWAYS_INLINE shared_ref_counter::shared_ref_counter(
        shared_ref_counter &&rhs) noexcept
        : _metadata{rhs._metadata}
    {
        rhs._metadata = nullptr;
    }

    VRM_CORE_ALWAYS_INLINE auto &shared_ref_counter::operator=(
        shared_ref_counter &&rhs) noexcept
    {
        _metadata = rhs._metadata;
        rhs._metadata = nullptr;
        return *this;
    }

    VRM_CORE_ALWAYS_INLINE bool VRM_CORE_PURE_FN
    shared_ref_counter::is_null() const noexcept
    {
        return _metadata == nullptr;
    }

    VRM_CORE_ALWAYS_INLINE auto VRM_CORE_PURE_FN
    shared_ref_counter::owner_count() const noexcept
    {
        return access_metadata().owner_count();
    }

    VRM_CORE_ALWAYS_INLINE auto VRM_CORE_PURE_FN
    shared_ref_counter::use_count() const noexcept
    {
        // TODO: owner count?

        return is_null() ? 0 : owner_count();
    }

    void shared_ref_counter::acquire_from_null()
    {
        VRM_CORE_ASSERT(is_null());
        _metadata = new shared_metadata{1, 0};
        // TODO: could throw `std::bad_alloc`.
    }

    VRM_CORE_ALWAYS_INLINE void shared_ref_counter::acquire_existing() noexcept
    {
        VRM_CORE_ASSERT(!is_null());
        increment_owner();
    }

    VRM_CORE_ALWAYS_INLINE void shared_ref_counter::increment_weak() noexcept
    {
        access_metadata().increment_weak();
    }

    template <typename TF>
    void shared_ref_counter::lose_ownership(TF &&deleter) noexcept
    {
        decrement_owner();
        deallocate_if_required(FWD(deleter));
    }

    template <typename TF>
    void shared_ref_counter::lose_weak(TF &&deleter)
    {
        decrement_weak();
        deallocate_if_required(FWD(deleter));
    }
} // namespace vrm::core::resource::impl
