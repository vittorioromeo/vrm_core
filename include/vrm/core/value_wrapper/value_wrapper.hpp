// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <utility>
#include <vrm/core/assert/static_assert_macros.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_traits/callable.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Class with a similar interface to `std::reference_wrapper` that
    /// uses value semantics.
    /// @details Stores `T` interally as a value. Useful for generic code that
    /// conditionally needs an `std::reference_wrapper`.
    template <typename T>
    class value_wrapper
    {
        VRM_CORE_STATIC_ASSERT_NM(!std::is_reference<T>{});

    private:
        T _value;

    public:
        using type = T;

        template <typename TFwd>
        VRM_CORE_ALWAYS_INLINE constexpr value_wrapper(TFwd&& x) noexcept(
            std::is_nothrow_constructible<T, TFwd&&>{})
            : _value(FWD(x))
        {
        }

        template <typename... TArgs,
            typename = std::enable_if_t<callable<T&(TArgs&&...)>>>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
            TArgs&&... args) noexcept(noexcept(_value(FWD(args)...)))
        {
            return _value(FWD(args)...);
        }

        template <typename... TArgs,
            typename = std::enable_if_t<callable<const T&(TArgs&&...)>>>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()(
            TArgs&&... args) const noexcept(noexcept(_value(FWD(args)...)))
        {
            return _value(FWD(args)...);
        }

        VRM_CORE_ALWAYS_INLINE constexpr auto& get() & noexcept
        {
            return _value;
        }

        VRM_CORE_ALWAYS_INLINE constexpr const auto& get() const & noexcept
        {
            return _value;
        }

        VRM_CORE_ALWAYS_INLINE constexpr T get() &&
            noexcept(std::is_nothrow_move_constructible<T>{})
        {
            return std::move(_value);
        }

        VRM_CORE_ALWAYS_INLINE constexpr operator T&() & noexcept
        {
            return _value;
        }

        VRM_CORE_ALWAYS_INLINE constexpr operator const T&() const noexcept
        {
            return _value;
        }

        VRM_CORE_ALWAYS_INLINE constexpr operator T() &&
            noexcept(std::is_nothrow_move_constructible<T>{})
        {
            return std::move(_value);
        }
    };
}
VRM_CORE_NAMESPACE_END
