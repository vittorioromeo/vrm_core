// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <type_traits>
#include <utility>
#include <vrm/core/utility_macros/fwd.hpp>
#include <vrm/core/config.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TF>
        class y_combinator_result
        {
        private:
            TF _f;

        public:
            template <typename T>
            inline explicit y_combinator_result(T&& f) noexcept : _f(FWD(f))
            {
            }

            template <typename... Ts>
            inline decltype(auto) operator()(Ts&&... xs)
            {
                return _f(std::ref(*this), FWD(xs)...);
            }
        };
    }

    template <typename TF>
    decltype(auto) y_combinator(TF && fun) noexcept
    {
        return impl::y_combinator_result<std::decay_t<TF>>(FWD(fun));
    }
}
VRM_CORE_NAMESPACE_END
