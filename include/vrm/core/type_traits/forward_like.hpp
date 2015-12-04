// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_traits/referenceness.hpp>
#include <vrm/core/assert/static_assert_macros.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Alias for the type that `T` would have as if it was forwarded
    /// like `TSource`.
    /// @details Does not check for possible incongruences. Example: if the
    /// input type `T` is an rvalue and the source type `TSource` is an lvalue,
    /// `T&` will be computed.
    template <typename T, typename TSource>
    using as_if_forwarded = std::conditional_t<!std::is_reference<TSource>{},
        std::add_rvalue_reference_t<std::remove_reference_t<T>>,
        copy_referenceness<T, TSource>>;

    /// @brief Casts the passed forwarding reference `x` as if it was being
    /// forwarded as `TLike`.
    template <typename TLike, typename T>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) forward_like(
        T && x) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(!(std::is_rvalue_reference<decltype(x)>{} &&
                                    std::is_lvalue_reference<TLike>{}));

        return static_cast<as_if_forwarded<T, TLike>>(x);
    }
}
VRM_CORE_NAMESPACE_END
