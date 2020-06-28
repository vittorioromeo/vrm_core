// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/casts/arithmetic.hpp>
#include <vrm/core/config.hpp>

#include <string>
#include <type_traits>

namespace vrm::core
{
    /// @brief Converts a string to `int`.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto str_to_int(const char* x)
    {
        char* end;
        return to_int(std::strtol(x, &end, 10));
    }

    /// @brief Converts a string to `float`.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto str_to_float(const char* x)
    {
        char* end;
        return to_float(std::strtof(x, &end));
    }

    /// @brief Converts a string to `double`.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto str_to_double(const char* x)
    {
        char* end;
        return to_double(std::strtod(x, &end));
    }

    /// @brief Converts a string to `sz_t`.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto str_to_size_t(const char* x)
    {
        char* end;
        return to_sz_t(std::strtoll(x, &end, 10));
    }

    /// @brief Converts a string to `int`.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto str_to_int(const std::string& x)
    {
        return str_to_int(x.c_str());
    }

    /// @brief Converts a string to `float`.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto str_to_float(const std::string& x)
    {
        return str_to_float(x.c_str());
    }

    /// @brief Converts a string to `double`.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto str_to_double(
        const std::string& x)
    {
        return str_to_double(x.c_str());
    }

    /// @brief Converts a string to `sz_t`.
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto str_to_size_t(
        const std::string& x)
    {
        return str_to_size_t(x.c_str());
    }
} // namespace vrm::core
