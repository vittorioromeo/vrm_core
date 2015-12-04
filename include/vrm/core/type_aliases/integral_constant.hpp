// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cstddef>
#include <type_traits>
#include <vrm/pp/cat.hpp>
#include <vrm/core/config/names.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

// TODO: comment
// TODO: auto-generate literal operator (with extra macro parameter)?

#define VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER(type, name)          \
    template <type TV>                                                      \
    using VRM_PP_CAT(name, _constant) = ::std::integral_constant<type, TV>; \
                                                                            \
    template <type TV>                                                      \
    using VRM_PP_CAT(name, _) = VRM_PP_CAT(name, _constant)<TV>;            \
                                                                            \
    template <type TV>                                                      \
    constexpr VRM_PP_CAT(name, _)<TV> VRM_PP_CAT(name, _, v){};

#define VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(x) \
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER(x, x)

VRM_CORE_NAMESPACE
{
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(char)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(short)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(int)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(long)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(llong)

    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(uchar)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(ushort)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(uint)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(ulong)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(ullong)

    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(bool)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(sz_t)
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN
#undef VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER
