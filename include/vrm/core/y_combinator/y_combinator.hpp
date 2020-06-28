// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

#include <functional>
#include <type_traits>
#include <utility>

namespace vrm::core
{
    namespace impl
    {
        template <typename TF>
        class y_combinator_result
        {
        private:
            using this_type = y_combinator_result<TF>;
            TF _f;

        public:
            template <typename T>
            VRM_CORE_ALWAYS_INLINE // .
                constexpr explicit y_combinator_result(T&& f) noexcept
                : _f(FWD(f))
            {
            }

            template <typename... Ts>
            [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)
            operator()(Ts&&... xs) noexcept(noexcept(                 // .
                _f(std::declval<std::reference_wrapper<this_type>>(), // .
                    FWD(xs)...)                                       // .
                ))
            {
                return _f(std::ref(*this), FWD(xs)...);
            }
        };
    } // namespace impl

    template <typename TF>
    [[nodiscard]] VRM_CORE_ALWAYS_INLINE constexpr auto y_combinator(
        TF&& f) noexcept
    {
        return impl::y_combinator_result<std::decay_t<TF>>(FWD(f));
    }
} // namespace vrm::core
