// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/tuple_utils/ref_tuple.hpp>
#include <vrm/core/casts/self.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Returns the `TN`-th argument of a variadic argument pack, casting
    /// it to the type it would have when wrapped into a `ref_tuple`.
    /// @details The casted type is a reference if the argument is an lvalue, a
    /// value (moved) if the argument is an rvalue.
    template <sz_t TN, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) nth_arg(Ts && ... xs) // .
        noexcept(noexcept(std::get<TN>(make_ref_tuple(FWD(xs)...))))
    {
        // Assert index validity.
        VRM_CORE_STATIC_ASSERT_NM(sizeof...(xs) > TN);

        // Type of a `ref_tuple` built with `xs...`.
        using ref_tuple_type = decltype(make_ref_tuple(FWD(xs)...));

        // Type of the `TN`-th argument of the `ref_tuple`.
        using nth_arg_type = std::tuple_element_t<TN, ref_tuple_type>;

        // Return the `TN`-th element of, casted to `nth_arg_type`.
        return self_cast<nth_arg_type>(
            std::get<TN>(make_ref_tuple(FWD(xs)...)));
    }
}
VRM_CORE_NAMESPACE_END

// TODO: check generated assembly
