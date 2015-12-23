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

// TODO: auto-generate literal operator (with extra macro parameter)?

/// @macro `xxx_constant` alias token.
#define VRM_CORE_IMPL_IC_ALIAS(type, name) VRM_PP_CAT(name, _constant)

/// @macro `xxx_` alias token.
#define VRM_CORE_IMPL_IC_SHORT_ALIAS(type, name) VRM_PP_CAT(name, _)

/// @macro `xxx_v` variable template name token.
#define VRM_CORE_IMPL_IC_SHORT_ALIAS_V(type, name) VRM_PP_CAT(name, _v)

/// @macro `is_xxx_constant_helper` struct name token.
#define VRM_CORE_IMPL_IS_IC_HELPER(type, name) \
    VRM_PP_CAT(is_, name, _constant_helper)

/// @macro `is_xxx_constant` alias token.
#define VRM_CORE_IMPL_IS_IC(type, name) VRM_PP_CAT(is_, name, _constant)

/// @macro `is_xxx_constant_v` variable template name
/// token.
#define VRM_CORE_IMPL_IS_IC_V(type, name) VRM_PP_CAT(is_, name, _constant_v)

/// @macro Defines an `integral-constant`-like type with
/// helper classes and aliases.
#define VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER(type, name)             \
    template <type TV>                                                         \
    using VRM_CORE_IMPL_IC_ALIAS(type, name) =                                 \
        ::std::integral_constant<type, TV>;                                    \
                                                                               \
    template <type TV>                                                         \
    using VRM_CORE_IMPL_IC_SHORT_ALIAS(type, name) =                           \
        VRM_CORE_IMPL_IC_ALIAS(type, name)<TV>;                                \
                                                                               \
    template <type TV>                                                         \
    constexpr VRM_CORE_IMPL_IC_SHORT_ALIAS(                                    \
        type, name)<TV> VRM_CORE_IMPL_IC_SHORT_ALIAS_V(type, name){};          \
                                                                               \
    namespace impl                                                             \
    {                                                                          \
        template <typename T>                                                  \
        struct VRM_CORE_IMPL_IS_IC_HELPER(type, name)                          \
            : ::std::false_type                                                \
        {                                                                      \
        };                                                                     \
                                                                               \
        template <type TV>                                                     \
        struct VRM_CORE_IMPL_IS_IC_HELPER(                                     \
            type, name)<::std::integral_constant<type, TV>> : ::std::true_type \
        {                                                                      \
        };                                                                     \
    }                                                                          \
                                                                               \
    template <typename T>                                                      \
    using VRM_CORE_IMPL_IS_IC(type, name) =                                    \
        impl::VRM_CORE_IMPL_IS_IC_HELPER(type, name)<T>;                       \
                                                                               \
    template <typename T>                                                      \
    constexpr VRM_CORE_IMPL_IS_IC(type, name)<T> VRM_CORE_IMPL_IS_IC_V(        \
        type, name){};

/// @macro Defines an `integral-constant`-like type with
/// helper classes and aliases. (The name of the input type is used in the
/// output type.)
#define VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(x) \
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER(x, x)

VRM_CORE_NAMESPACE
{
    // Signed integral constants.
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(char)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(short)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(int)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(long)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(llong)

    // Unsigned integral constants.
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(uchar)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(ushort)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(uint)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(ulong)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(ullong)

    // Special integral constants.
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(bool)
    VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN(sz_t)
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER_SN
#undef VRM_CORE_IMPL_DEFINE_INTEGRAL_CONSTANT_WRAPPER
#undef VRM_CORE_IMPL_IS_IC_V
#undef VRM_CORE_IMPL_IS_IC
#undef VRM_CORE_IMPL_IS_IC_HELPER
#undef VRM_CORE_IMPL_IC_SHORT_ALIAS_V
#undef VRM_CORE_IMPL_IC_SHORT_ALIAS
#undef VRM_CORE_IMPL_IC_ALIAS
