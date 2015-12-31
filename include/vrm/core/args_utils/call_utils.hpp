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

VRM_CORE_NAMESPACE
{
#define VRM_CORE_IMPL_BODY() \
    impl::args_call_wrapper( \
        impl::first_n_args_wrapper<TN>{}, FWD(f), FWD(xs)...)

    template <sz_t TN, typename TF, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)   // .
        call_with_first_n_args(TF && f, Ts && ... xs) // .
        VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY()

#undef VRM_CORE_IMPL_BODY



#define VRM_CORE_IMPL_BODY() \
    impl::args_call_wrapper(impl::last_n_args_wrapper<TN>{}, FWD(f), FWD(xs)...)

            template <sz_t TN, typename TF, typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        call_with_last_n_args(TF && f, Ts && ... xs)        // .
        VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY()

#undef VRM_CORE_IMPL_BODY



#define VRM_CORE_IMPL_BODY() \
    impl::args_call_wrapper( \
        impl::all_args_from_wrapper<TN>{}, FWD(f), FWD(xs)...)

            template <sz_t TN, typename TF, typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) // .
        call_with_all_args_from(TF && f, Ts && ... xs)      // .
        VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY()

#undef VRM_CORE_IMPL_BODY
}
VRM_CORE_NAMESPACE_END
