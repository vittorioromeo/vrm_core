// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config/names.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T, typename TSource>
        using copy_referenceness_impl =
            std::conditional_t<!std::is_reference<TSource>{}, T,
                std::conditional_t<std::is_lvalue_reference<TSource>{},
                    std::add_lvalue_reference_t<T>,
                    std::add_rvalue_reference_t<T>>>;
    }

    /// @brief Removes reference from `T`, then applies `TSource`'s
    /// "referenceness" to it.
    template <typename T, typename TSource>
    using copy_referenceness =
        impl::copy_referenceness_impl<std::remove_reference_t<T>, TSource>;
}
VRM_CORE_NAMESPACE_END
