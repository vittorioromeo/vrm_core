// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

namespace vrm::core::impl
{
    /// @brief Empty implementation `struct` used to "mark" strong typedefs.
    struct strong_typedef_marker
    {
    };
} // namespace vrm::core::impl

#define VRM_CORE_STRONG_TYPEDEF(underlying, name)                             \
    class name final                                                          \
    {                                                                         \
    public:                                                                   \
        using strong_typedef_tag = ::vrm::core::impl::strong_typedef_marker;  \
        using underlying_type = underlying;                                   \
                                                                              \
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
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr                        \
        operator const underlying&() const noexcept                           \
        {                                                                     \
            return _value;                                                    \
        }                                                                     \
                                                                              \
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr                        \
        operator underlying&() noexcept                                       \
        {                                                                     \
            return _value;                                                    \
        }                                                                     \
                                                                              \
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)         \
        operator==(const name& rhs) noexcept                                  \
        {                                                                     \
            return _value == rhs._value;                                      \
        }                                                                     \
                                                                              \
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)         \
        operator!=(const name& rhs) noexcept                                  \
        {                                                                     \
            return _value != rhs._value;                                      \
        }                                                                     \
                                                                              \
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)         \
        operator<(const name& rhs) noexcept                                   \
        {                                                                     \
            return _value < rhs._value;                                       \
        }                                                                     \
                                                                              \
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)         \
        operator>(const name& rhs) noexcept                                   \
        {                                                                     \
            return _value > rhs._value;                                       \
        }                                                                     \
                                                                              \
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)         \
        operator<=(const name& rhs) noexcept                                  \
        {                                                                     \
            return _value <= rhs._value;                                      \
        }                                                                     \
                                                                              \
        [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)         \
        operator>=(const name& rhs) noexcept                                  \
        {                                                                     \
            return _value >= rhs._value;                                      \
        }                                                                     \
    };                                                                        \
                                                                              \
    static_assert(std::is_literal_type<name>{});                              \
    static_assert(std::is_literal_type<underlying>{})
