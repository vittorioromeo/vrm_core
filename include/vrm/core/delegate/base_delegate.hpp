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
        private:
            using this_type = base_delegate<TReturn(TArgs...)>;

        public:
            using fn_type = std::function<TReturn(TArgs...)>;

        protected:
            std::vector<fn_type> _functions;

            template <typename TF>
            void emplace_function(TF&& f)
            {
                _functions.emplace_back(FWD(f));
            }

            template <typename TSelf, typename... Ts>
            static void call_impl(TSelf&& self, Ts&&... xs) // .
                noexcept(noexcept(self._functions.back()(xs...)))
            {
                for(auto&& f : self._functions) f(xs...);
            }

            template <typename TSelf, typename TF, typename... Ts>
            static void call_and_use_result_impl                // .
                (TSelf&& self, TF&& result_handler, Ts&&... xs) // .
                noexcept(
                    noexcept(result_handler(self._functions.back()(xs...))))
            {
                for(auto&& f : self._functions) result_handler(f(xs...));
            }

            template <typename TSelf, typename... Ts>
            static auto call_and_return_vector_impl(TSelf&& self, Ts&&... xs)
            {
                std::vector<TReturn> result;
                result.reserve(self._functions.size());

                self.call_and_use_result(
                    [&result](auto&& x)
                    {
                        result.emplace_back(FWD(x));
                    },
                    FWD(xs)...);

                return result;
            }

        public:
            template <typename TF, typename... Ts>
            void call_and_use_result(TF&& result_handler, Ts&&... xs) // .
                noexcept(noexcept(call_and_use_result_impl(
                    this_type{}, FWD(result_handler), FWD(xs)...)))
            {
                return call_and_use_result_impl(
                    *this, FWD(result_handler), FWD(xs)...);
            }

            template <typename TF, typename... Ts>
            void call_and_use_result(TF&& result_handler, Ts&&... xs) const // .
                noexcept(noexcept(call_and_use_result_impl(
                    this_type{}, FWD(result_handler), FWD(xs)...)))
            {
                return call_and_use_result_impl(
                    *this, FWD(result_handler), FWD(xs)...);
            }

            template <typename... Ts>
            void operator()(Ts&&... xs) // .
                noexcept(noexcept(call_impl(this_type{}, FWD(xs)...)))
            {
                return call_impl(*this, FWD(xs)...);
            }

            template <typename... Ts>
            void operator()(Ts&&... xs) const // .
                noexcept(noexcept(call_impl(this_type{}, FWD(xs)...)))
            {
                return call_impl(*this, FWD(xs)...);
            }

            template <typename... Ts>
            auto call_and_return_vector(Ts&&... xs) // .
                noexcept(noexcept(
                    call_and_return_vector_impl(this_type{}, FWD(xs)...)))
            {
                return call_and_return_vector_impl(*this, FWD(xs)...);
            }

            template <typename... Ts>
            auto call_and_return_vector(Ts&&... xs) const // .
                noexcept(noexcept(
                    call_and_return_vector_impl(this_type{}, FWD(xs)...)))
            {
                return call_and_return_vector_impl(*this, FWD(xs)...);
            }

            void reserve(std::size_t x) { _functions.reserve(x); }
            void clear() noexcept { _functions.clear(); }
            const auto& empty() const noexcept { return _functions.empty(); }
        };
    }
}
VRM_CORE_NAMESPACE_END