// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <utility>
#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

namespace vrm::core
{
    namespace impl
    {
        /// @brief Returns a `ref_tuple` from a variadic pack.
        /// @details Given an index sequence, a starting index and a variadic
        /// amount of arguments, returns a `ref_tuple` of the arguments with
        /// matching indices. The `ref_tuple` avoids copies: lvalues are taken
        /// as reference, rvalues are moved in the resulting tuple.
        template <sz_t TIBegin, sz_t... TIs, typename... Ts>
        constexpr auto build_args_slice(
            std::index_sequence<TIs...>, Ts&&... xs) noexcept;
    }

    /// @brief Returns a `[TIBegin, TIEnd)` slice of the variadic arguments.
    /// @details A `ref_tuple` is used to store the arguments.
    template <sz_t TIBegin, sz_t TIEnd, typename... Ts>
    constexpr auto args_slice(Ts && ... xs) noexcept;
}
