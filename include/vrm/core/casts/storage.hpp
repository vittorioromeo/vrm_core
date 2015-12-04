// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits/common.hpp>
#include <vrm/core/type_traits/qualifiers.hpp>
#include <vrm/core/type_traits/forward_like.hpp>
#include <vrm/core/ostream_utils/nullptr_printer.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a pointer.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) storage_cast(
        TStorage * storage) noexcept
    {
        VRM_CORE_STATIC_ASSERT(                           // .
            sizeof(typename TStorage::type) >= sizeof(T), // .
            "`TStorage` is not big enough for `T`.");

        VRM_CORE_STATIC_ASSERT(                             // .
            alignof(typename TStorage::type) >= alignof(T), // .
            "`TStorage` is not properly aligned for `T`.");

        VRM_CORE_ASSERT_OP(storage, !=, nullptr);

        using return_type = copy_cv_qualifiers<T, TStorage>;
        return reinterpret_cast<return_type*>(storage);
    }

    /// @brief Wrapper around `reinterpret_cast`, intended for use with
    /// aligned
    /// storages. Returns a reference.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) storage_cast(
        TStorage && storage) noexcept
    {
        return forward_like<decltype(storage)>(*storage_cast<T>(&storage));
    }
}
VRM_CORE_NAMESPACE_END
