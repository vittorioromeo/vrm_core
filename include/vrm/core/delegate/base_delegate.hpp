// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/internal.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename>
        class base_delegate;

        template <typename TReturn, typename... TArgs>
        class base_delegate<TReturn(TArgs...)>
        {
        public:
            using fn_type = std::function<TReturn(TArgs...)>;

        protected:
            std::vector<fn_type> _functions;

            template <typename TF>
            void emplace_function(TF&& f)
            {
                _functions.emplace_back(FWD(f));
            }

        public:
            template <typename TF, typename... Ts>
            void call_and_use_result(TF&& result_handler, Ts&&... xs) noexcept(
                noexcept(result_handler(_functions.back()(xs...))))
            {
                for(auto& f : _functions)
                {
                    result_handler(f(xs...));
                }
            }

            template <typename TF, typename... Ts>
            void call_and_use_result(TF&& result_handler, Ts&&... xs) const
                noexcept(noexcept(result_handler(_functions.back()(xs...))))
            {
                for(const auto& f : _functions)
                {
                    result_handler(f(xs...));
                }
            }

            template <typename... Ts>
            void operator()(Ts&&... xs) noexcept(
                noexcept(_functions.back()(xs...)))
            {
                for(auto& f : _functions)
                {
                    f(xs...);
                }
            }

            template <typename... Ts>
            void operator()(Ts&&... xs) const
                noexcept(noexcept(_functions.back()(xs...)))
            {
                for(const auto& f : _functions)
                {
                    f(xs...);
                }
            }

            template <typename... Ts>
            auto call_and_return_vector(Ts&&... xs)
            {
                std::vector<TReturn> result;
                result.reserve(_functions.size());
                this->call_and_use_result(
                    [&result](auto&& x)
                    {
                        result.emplace_back(FWD(x));
                    },
                    FWD(xs)...);

                return result;
            }

            template <typename... Ts>
            auto call_and_return_vector(Ts&&... xs) const
            {
                std::vector<TReturn> result;
                result.reserve(_functions.size());
                this->call_and_use_result(
                    [&result](auto&& x)
                    {
                        result.emplace_back(FWD(x));
                    },
                    FWD(xs)...);

                return result;
            }

            void reserve(std::size_t x) { _functions.reserve(x); }
            void clear() noexcept { _functions.clear(); }
            const auto& empty() const noexcept { return _functions.empty(); }
        };
    }
}
VRM_CORE_NAMESPACE_END