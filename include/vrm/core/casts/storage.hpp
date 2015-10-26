// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits.hpp>
#include <vrm/core/ostream_utils.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a `T*`.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) from_storage(
        TStorage * storage) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(valid_storage<T, TStorage>{});
        VRM_CORE_ASSERT_OP(storage, !=, nullptr);

        return reinterpret_cast<T*>(storage);
    }

    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a `T&`.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) from_storage(
        TStorage & storage) noexcept
    {
        return *from_storage<T>(&storage);
    }

    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a `const T*`.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) from_storage(
        const TStorage* storage) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(valid_storage<T, TStorage>{});
        VRM_CORE_ASSERT_OP(storage, !=, nullptr);

        return reinterpret_cast<const T*>(storage);
    }

    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a `const T&`.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) from_storage(
        const TStorage& storage) noexcept
    {
        return *from_storage<T>(&storage);
    }
}
VRM_CORE_NAMESPACE_END