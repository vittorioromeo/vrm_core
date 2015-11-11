// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <string>
#include <vrm/core/config.hpp>
#include <vrm/core/casts/arithmetic.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Converts a string to `int`.
    VRM_CORE_ALWAYS_INLINE auto str_to_int(const char* x)
    {
        char* end;
        return to_int(std::strtol(x, &end, 10));
    }

    /// @brief Converts a string to `float`.
    VRM_CORE_ALWAYS_INLINE auto str_to_float(const char* x)
    {
        char* end;
        return to_float(std::strtof(x, &end));
    }

    /// @brief Converts a string to `double`.
    VRM_CORE_ALWAYS_INLINE auto str_to_double(const char* x)
    {
        char* end;
        return to_double(std::strtod(x, &end));
    }

    /// @brief Converts a string to `sz_t`.
    VRM_CORE_ALWAYS_INLINE auto str_to_size_t(const char* x)
    {
        char* end;
        return to_sz_t(std::strtoll(x, &end, 10));
    }

    /// @brief Converts a string to `int`.
    VRM_CORE_ALWAYS_INLINE auto str_to_int(const std::string& x)
    {
        return str_to_int(x.c_str());
    }

    /// @brief Converts a string to `float`.
    VRM_CORE_ALWAYS_INLINE auto str_to_float(const std::string& x)
    {
        return str_to_float(x.c_str());
    }

    /// @brief Converts a string to `double`.
    VRM_CORE_ALWAYS_INLINE auto str_to_double(const std::string& x)
    {
        return str_to_double(x.c_str());
    }

    /// @brief Converts a string to `sz_t`.
    VRM_CORE_ALWAYS_INLINE auto str_to_size_t(const std::string& x)
    {
        return str_to_size_t(x.c_str());
    }
}
VRM_CORE_NAMESPACE_END
