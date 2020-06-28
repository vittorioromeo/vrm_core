// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/args_utils/args_slice.hpp>
#include <vrm/core/args_utils/args_slice_aliases.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/tuple_utils/apply.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/pp.hpp>

/// @macro Defines a `constexpr`-friendly struct that wraps an arg-slicing
/// function. The struct has name `name` and wraps the function `fn`.
#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER(name, fn)           \
    template <sz_t TN>                                              \
    struct name final                                               \
    {                                                               \
        template <typename... Ts>                                   \
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()( \
            Ts&&... xs) noexcept                                    \
        {                                                           \
            return fn<TN>(FWD(xs)...);                              \
        }                                                           \
    };

/// @macro Defines a `constexpr`-friendly struct that wraps an arg-slicing
/// function. The struct's name is the concatenation of `fn` and `_wrapper`.
#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(fn) \
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER(VRM_PP_CAT(fn, _wrapper), fn)

namespace vrm::core
{
    namespace impl
    {
        /// @brief Defines a wrapper that, after slicing a variadic argument
        /// pack, applies the resulting `ref_tuple` to the function `f`.
        /// @details The used slicing function is passed in as `TFArgGetter`,
        /// under the form of a `constexpr`-friendly wrapper.
        template <typename TFArgGetter, typename TF, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr auto              // .
        args_call_wrapper(TFArgGetter, TF&& f, Ts&&... xs) // .
            VRM_CORE_RETURNS(                              // .
                apply(f, TFArgGetter{}(FWD(xs)...))        // .
            )
    } // namespace impl

    namespace impl
    {
        // Call the macros to define all wrappers.
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(first_n_args)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(last_n_args)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(all_args_from)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(all_args_after)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(all_args_until)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(all_args_before)
    } // namespace impl
} // namespace vrm::core

#undef VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN
#undef VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER
