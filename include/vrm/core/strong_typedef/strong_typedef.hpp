// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/assert/static_assert_macros.hpp>

#define VRM_CORE_STRONG_TYPEDEF(underlying, name)                             \
    class name final                                                          \
    {                                                                         \
    private:                                                                  \
        underlying _value;                                                    \
                                                                              \
    public:                                                                   \
        VRM_CORE_ALWAYS_INLINE name() noexcept = default;                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE name(const name&) = default;                   \
        VRM_CORE_ALWAYS_INLINE name(name&&) = default;                        \
                                                                              \
        VRM_CORE_ALWAYS_INLINE name& operator=(const name&) = default;        \
        VRM_CORE_ALWAYS_INLINE name& operator=(name&&) = default;             \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr explicit name(underlying x) noexcept \
            : _value{x}                                                       \
        {                                                                     \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr name& operator=(                     \
            underlying rhs) noexcept                                          \
        {                                                                     \
            _value = rhs;                                                     \
            return *this;                                                     \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr operator const underlying&() const   \
            noexcept                                                          \
        {                                                                     \
            return _value;                                                    \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr operator underlying&() noexcept      \
        {                                                                     \
            return _value;                                                    \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator==(           \
            const name& rhs) noexcept                                         \
        {                                                                     \
            return _value == rhs._value;                                      \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator!=(           \
            const name& rhs) noexcept                                         \
        {                                                                     \
            return _value != rhs._value;                                      \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator<(            \
            const name& rhs) noexcept                                         \
        {                                                                     \
            return _value < rhs._value;                                       \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator>(            \
            const name& rhs) noexcept                                         \
        {                                                                     \
            return _value > rhs._value;                                       \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator<=(           \
            const name& rhs) noexcept                                         \
        {                                                                     \
            return _value <= rhs._value;                                      \
        }                                                                     \
                                                                              \
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator>=(           \
            const name& rhs) noexcept                                         \
        {                                                                     \
            return _value >= rhs._value;                                      \
        }                                                                     \
    };                                                                        \
                                                                              \
    VRM_CORE_STATIC_ASSERT_NM(std::is_literal_type<name>{});                  \
    VRM_CORE_STATIC_ASSERT_NM(std::is_literal_type<underlying>{})

