// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp.hpp>
#include <vrm/core/utility_macros/impl/noexcept.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/tuple_utils/apply.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>
#include <vrm/core/args_utils/args_slice.hpp>
#include <vrm/core/args_utils/args_slice_aliases.hpp>
#include <vrm/core/args_utils/impl/wrappers.hpp>

// TODO: docs and tests

#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_WRAPPER_FN(fn) \
    impl::VRM_PP_CAT(fn, _wrapper)

#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_BODY(fn)                  \
    impl::args_call_wrapper(                                             \
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_WRAPPER_FN(fn) < TN > {}, \
        FWD(f), FWD(xs)...)

#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER(name, fn)                     \
    template <sz_t TN, typename TF, typename... Ts>                          \
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) name(TF&& f, Ts&&... xs) \
        VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY_VA(                           \
            VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_BODY(fn))

#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER_SN(fn) \
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_CALLER(VRM_PP_CAT(call_with_, fn), fn)

VRM_CORE_NAMESPACE
{
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
