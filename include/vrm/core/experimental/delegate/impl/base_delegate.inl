// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <vector>
#include <vrm/core/config.hpp>
#include <vrm/core/experimental/delegate/impl/base_delegate.hpp>
#include <vrm/core/experimental/delegate/signature_helper.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <typename TSettings>
        template <typename TF>
        void base_delegate<TSettings>::emplace_function(TF&& f)
        {
            _functions.emplace_back(FWD(f));
        }

        template <typename TSettings>
        template <typename TSelf, typename TF, typename... Ts>
        void base_delegate<TSettings>::                     // .
            call_and_use_result_impl                        // .
            (TSelf&& self, TF&& result_handler, Ts&&... xs) // .
            noexcept(noexcept(result_handler(self._functions.back()(xs...))))
        {
            for(auto&& f : self._functions) result_handler(f(xs...));
        }

        template <typename TSettings>
        template <typename TSelf, typename... Ts>
        void base_delegate<TSettings>:: // .
            call_impl                   // .
            (TSelf&& self, Ts&&... xs)  // .
            noexcept(noexcept(self._functions.back()(xs...)))
        {
            for(auto&& f : self._functions) f(xs...);
        }

        template <typename TSettings>
        template <typename TSelf, typename... Ts>
        auto base_delegate<TSettings>:: // .
            call_and_return_vector_impl // .
            (TSelf&& self, Ts&&... xs)
        {
            std::vector<fn_return_type> result;
            result.reserve(self._functions.size());

            call_and_use_result_impl(
                FWD(self), [&result](auto&& x) { result.emplace_back(FWD(x)); },
                FWD(xs)...);

            return result;
        }

#define VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(qualifier)            \
    template <typename TSettings>                                           \
    template <typename TF, typename... Ts>                                  \
    auto base_delegate<TSettings>::call_and_use_result(                     \
        TF&& result_handler, Ts&&... xs)                                    \
        qualifier noexcept(noexcept(call_and_use_result_impl(               \
            this_type{}, result_handler, FWD(xs)...)))                      \
    {                                                                       \
        return call_and_use_result_impl(*this, result_handler, FWD(xs)...); \
    }                                                                       \
                                                                            \
    template <typename TSettings>                                           \
    template <typename... Ts>                                               \
    auto base_delegate<TSettings>::operator()(Ts&&... xs)                   \
        qualifier noexcept(noexcept(call_impl(this_type{}, FWD(xs)...)))    \
    {                                                                       \
        return call_impl(*this, FWD(xs)...);                                \
    }                                                                       \
                                                                            \
    template <typename TSettings>                                           \
    template <typename... Ts>                                               \
    auto base_delegate<TSettings>::call_and_return_vector(Ts&&... xs)       \
        qualifier noexcept(                                                 \
            noexcept(call_and_return_vector_impl(this_type{}, FWD(xs)...))) \
    {                                                                       \
        return call_and_return_vector_impl(*this, FWD(xs)...);              \
    }

        VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(&)
        VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(const&)
        VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(&&)

#undef VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS

        template <typename TSettings>
        void base_delegate<TSettings>::reserve(sz_t x)
        {
            _functions.reserve(x);
        }

        template <typename TSettings>
        void base_delegate<TSettings>::clear() noexcept
        {
            _functions.clear();
        }

        template <typename TSettings>
        auto base_delegate<TSettings>::empty() const noexcept
        {
            return _functions.empty();
        }
    } // namespace impl
} // namespace vrm::core
