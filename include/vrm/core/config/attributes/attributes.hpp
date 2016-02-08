// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

/// @macro Macro that expands to an attribute. (Implementation.)
#define VRM_CORE_IMPL_ATTRIBUTE(...) __attribute__((__VA_ARGS__))

/// @macro Macro that expands to an attribute.
/// @details Uses ` __attribute__`.
#define VRM_CORE_ATTRIBUTE(...) VRM_CORE_IMPL_ATTRIBUTE(__VA_ARGS__)

/// @macro Expands to the `unused` attribute.
#define VRM_CORE_UNUSED VRM_CORE_ATTRIBUTE(unused)

/// @macro Expands to the `always_inline` attribute.
/// @details Generally, functions are not inlined unless optimization is
/// specified. For functions declared inline, this attribute inlines the
/// function independent of any restrictions that otherwise apply to inlining.
/// Failure to inline such a function is diagnosed as an error. Note that if
/// such a function is called indirectly the compiler may or may not inline it
/// depending on optimization level and a failure to inline an indirect call may
/// or may not be diagnosed.
/// (From GCC documentation.)
#define VRM_CORE_ALWAYS_INLINE VRM_CORE_ATTRIBUTE(always_inline) inline

/// @macro Expands to the `noinline` attribute.
/// @details This function attribute prevents a function from being considered
/// for inlining. If the function does not have side-effects, there are
/// optimizations other than inlining that cause function calls to be optimized
/// away, although the function call is live.
/// (From GCC documentation.)
#define VRM_CORE_NEVER_INLINE VRM_CORE_ATTRIBUTE(noinline)

/// @macro Expands to the `unused` attribute.
/// @details This attribute, attached to a function, means that the function is
/// meant to be possibly unused. GCC does not produce a warning for this
/// function.
/// (From GCC documentation.)
#define VRM_CORE_UNUSED_FN VRM_CORE_UNUSED

/// @macro Expands to the `pure` attribute.
/// @details Many functions have no effects except the return value and their
/// return value depends only on the parameters and/or global variables. Such a
/// function can be subject to common subexpression elimination and loop
/// optimization just as an arithmetic operator would be. These functions should
/// be declared with the attribute pure.
/// (From GCC documentation.)
#define VRM_CORE_PURE_FN VRM_CORE_ATTRIBUTE(pure)

/// @macro Expands to the `const` attribute.
/// @details Many functions do not examine any values except their arguments,
/// and have no effects except the return value. Basically this is just slightly
/// more strict class than the pure attribute below, since function is not
/// allowed to read global memory. Note that a function that has pointer
/// arguments and examines the data pointed to must not be declared const.
/// Likewise, a function that calls a non-const function usually must not be
/// const. It does not make sense for a const function to return void.
/// (From GCC documentation.)
#define VRM_CORE_CONST_FN VRM_CORE_ATTRIBUTE(const)

/// @macro Expands to the `noreturn` attribute.
/// @details A few standard library functions, such as abort and exit, cannot
/// return. GCC knows this automatically. Some programs define their own
/// functions that never return. You can declare them noreturn to tell the
/// compiler this fact. It does not make sense for a noreturn function to have a
/// return type other than void.
/// (From GCC documentation.)
#define VRM_CORE_NORETURN_FN VRM_CORE_ATTRIBUTE(noreturn)

// TODO: docs, conditional compilator depending on compiler if necessary
// TODO: function_attributes.hpp, class_attributes.hpp, ...
