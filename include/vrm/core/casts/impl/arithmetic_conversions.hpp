// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/casts/impl/arithmetic.hpp>
#include <vrm/core/casts/impl/overflow_check.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/pp/cat.hpp>

#define VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER(type, name)                  \
    template <typename T>                                                      \
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto VRM_PP_CAT(to_, name)( \
        T x) noexcept                                                          \
    {                                                                          \
        return to_num<type>(x);                                                \
    }

#define VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(type) \
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER(type, type)

namespace vrm::core
{
    // Floating-point types.
    /// @brief Converts a number to `float`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(float)

    /// @brief Converts a number to `double`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(double)

    /// @brief Converts a number to `ldouble`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(ldouble)



    // Signed types.
    /// @brief Converts a number to `char`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(char)

    /// @brief Converts a number to `short`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(short)

    /// @brief Converts a number to `int`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(int)

    /// @brief Converts a number to `long`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(long)

    /// @brief Converts a number to `llong`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(llong)



    // Unsigned types.
    /// @brief Converts a number to `uchar`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(uchar)

    /// @brief Converts a number to `ushort`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(ushort)

    /// @brief Converts a number to `uint`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(uint)

    /// @brief Converts a number to `ulong`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(ulong)

    /// @brief Converts a number to `ullong`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(ullong)



    // Sized signed integral constants.
    /// @brief Converts a number to `i8`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(i8)

    /// @brief Converts a number to `i16`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(i16)

    /// @brief Converts a number to `i32`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(i32)

    /// @brief Converts a number to `i64`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(i64)



    // Sized unsigned integral constants.
    /// @brief Converts a number to `ui8`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(ui8)

    /// @brief Converts a number to `ui16`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(ui16)

    /// @brief Converts a number to `ui32`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(ui32)

    /// @brief Converts a number to `ui64`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(ui64)



    // Special types.
    /// @brief Converts a number to `sz_t`.
    VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME(sz_t)
} // namespace vrm::core

#undef VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER_SAME_NAME
#undef VRM_CORE_IMPL_DEFINE_NUM_TO_NUM_CONVERTER
