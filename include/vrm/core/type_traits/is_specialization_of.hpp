// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief "False" case for template specialization checking.
    template <typename, template <typename...> class>
    struct is_specialization_of : std::false_type
    {
    };

    /// @brief "True" case for template specialization checking.
    template <template <typename...> class TTemplate, typename... Ts>
    struct is_specialization_of<TTemplate<Ts...>, TTemplate> : std::true_type
    {
    };

    /// @brief Evaluates to `std::true_type` if `T` is a specialization of
    /// `TTemplate`.
    template <typename T, template <typename...> class TTemplate>
    using is_specialization_of_t = is_specialization_of<T, TTemplate>;
}
VRM_CORE_NAMESPACE_END
