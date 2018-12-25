// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <iosfwd>
#include <utility>
#include <vrm/core/config.hpp>
#include <vrm/core/type_traits/detection.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <typename T>
        using ostreamable_detector =
            decltype(std::declval<std::ostream&>() << std::declval<const T&>());

        template <typename T>
        using istreamable_detector =
            decltype(std::declval<std::istream&>() >> std::declval<T&>());
    }

    /// @brief Evaluates to `std::true_type` if `T` can be streamed to an
    /// `std::ostream`, to `std::false_type` otherwise.
    template <typename T>
    constexpr is_detected<impl::ostreamable_detector, T> ostreamable{};

    /// @brief Evaluates to `std::true_type` if `T` can be streamed from an
    /// `std::istream`, to `std::false_type` otherwise.
    template <typename T>
    constexpr is_detected<impl::istreamable_detector, T> istreamable{};
}
