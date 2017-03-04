// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <iosfwd>
#include <utility>
#include <vrm/core/config.hpp>
#include <vrm/core/type_traits/detection.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T, typename... Ts>
        using callable_detector =
            decltype(std::declval<T>()(std::declval<Ts&&>()...));
    }

    /// @brief Evaluates to `std::true_type` if `T` can be invoked with `Ts...`,
    /// to `std::false_type` otherwise.
    template <typename T, typename... Ts>
    constexpr is_detected<impl::callable_detector, T, Ts...> callable{};
}
VRM_CORE_NAMESPACE_END
