// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>

namespace vrm::core
{
    namespace impl
    {
        template <typename T, typename TSource>
        using copy_referenceness_impl =
            std::conditional_t<!std::is_reference_v<TSource>, T,
                std::conditional_t<std::is_lvalue_reference_v<TSource>,
                    std::add_lvalue_reference_t<T>,
                    std::add_rvalue_reference_t<T>>>;
    } // namespace impl

    /// @brief Removes reference from `T`, then applies `TSource`'s
    /// "referenceness" to it.
    template <typename T, typename TSource>
    using copy_referenceness =
        impl::copy_referenceness_impl<std::remove_reference_t<T>, TSource>;
} // namespace vrm::core
