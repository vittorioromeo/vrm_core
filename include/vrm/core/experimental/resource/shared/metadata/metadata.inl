// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/assert/assert.hpp>
#include <vrm/core/experimental/resource/shared/metadata.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            VRM_CORE_ALWAYS_INLINE shared_metadata::shared_metadata(
                shared_counter_type owner_count,
                shared_counter_type weak_count) noexcept
                : _owner_count{owner_count},
                  _weak_count{weak_count}
            {
            }

            VRM_CORE_ALWAYS_INLINE void
            shared_metadata::increment_owner() noexcept
            {
                ++_owner_count;
            }

            VRM_CORE_ALWAYS_INLINE void
            shared_metadata::decrement_owner() noexcept
            {
                VRM_CORE_ASSERT_OP(_owner_count, >, 0);
                --_owner_count;
            }

            VRM_CORE_ALWAYS_INLINE void
            shared_metadata::increment_weak() noexcept
            {
                ++_weak_count;
            }

            VRM_CORE_ALWAYS_INLINE void
            shared_metadata::decrement_weak() noexcept
            {
                VRM_CORE_ASSERT_OP(_weak_count, >, 0);
                --_weak_count;
            }

            VRM_CORE_ALWAYS_INLINE auto // .
                shared_metadata::owner_count() const noexcept
            {
                return _owner_count;
            }

            VRM_CORE_ALWAYS_INLINE auto // .
                shared_metadata::weak_count() const noexcept
            {
                return _weak_count;
            }

            VRM_CORE_ALWAYS_INLINE auto // .
                shared_metadata::total_count() const noexcept
            {
                return owner_count() + weak_count();
            }

            VRM_CORE_ALWAYS_INLINE auto // .
                shared_metadata::has_any_ref() const noexcept
            {
                return total_count() > 0;
            }
        }
    }
}
VRM_CORE_NAMESPACE_END
