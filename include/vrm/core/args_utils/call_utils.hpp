// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/tuple_utils/apply.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>
#include <vrm/core/args_utils/args_slice.hpp>
#include <vrm/core/args_utils/args_slice_aliases.hpp>
#include <vrm/core/args_utils/impl/wrappers.hpp>

/// @macro Given an arg-slicing function `fn`, computes the name of the
/// `constexpr`-friendly `fn` wrapper.
#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_WRAPPER_FN(fn) \
    impl::VRM_PP_CAT(fn, _wrapper)

/// @macro Body of the call wrapper function. Given an arg-slicing function
/// `fn`, it instantiates a `constexpr`-friendly `fn` wrapper and calls it with
/// perfect-forwarding.
#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_BODY(fn)                  \
    impl::args_call_wrapper(                                             \
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_WRAPPER_FN(fn) < TN > {}, \
        FWD(f), FWD(xs)...)

/// @macro Defines an utility function to call another function with a slice of
/// variadic arguments.
#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER(name, fn)           \
    template <sz_t TN, typename TF, typename... Ts>                \
    VRM_CORE_ALWAYS_INLINE constexpr auto name(TF&& f, Ts&&... xs) \
        VRM_CORE_RETURNS(                                          \
            VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_BODY(fn))

/// @macro Defines an utility function to call another function with a slice of
/// variadic arguments. The name of the wrapper is created by concatenating
/// `call_with_` and `fn`, where `fn` is an arg-slicing function.
#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN(fn) \
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER(VRM_PP_CAT(call_with_, fn), fn)

VRM_CORE_NAMESPACE
{
    // Call the macros to define all call utility functions.
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN(first_n_args)
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN(last_n_args)
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN(all_args_from)
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN(all_args_after)
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN(all_args_until)
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN(all_args_before)
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN
#undef VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER
#undef VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_BODY
#undef VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_WRAPPER_FN
