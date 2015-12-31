// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros/fwd.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/experimental/delegate/signature_helper.hpp>
#include <vrm/core/experimental/delegate/impl/base_delegate.hpp>

#define VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(function, signature, allocator) \
    template <template <typename...> class function, typename signature,     \
        typename allocator>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        template <typename TF>
        void base_delegate<TFunction, TSignature, TAllocator>::emplace_function(
            TF&& f)
        {
            _functions.emplace_back(FWD(f));
        }

        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        template <typename TSelf, typename TF, typename... Ts>
        void base_delegate<TFunction, TSignature, TAllocator>:: // .
            call_and_use_result_impl                            // .
            (TSelf&& self, TF&& result_handler, Ts&&... xs)     // .
            noexcept(noexcept(result_handler(self._functions.back()(xs...))))
        {
            for(auto&& f : self._functions) result_handler(f(xs...));
        }

        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        template <typename TSelf, typename... Ts>
        void base_delegate<TFunction, TSignature, TAllocator>:: // .
            call_impl                                           // .
            (TSelf&& self, Ts&&... xs)                          // .
            noexcept(noexcept(self._functions.back()(xs...)))
        {
            for(auto&& f : self._functions) f(xs...);
        }

        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        template <typename TSelf, typename... Ts>
        auto base_delegate<TFunction, TSignature, TAllocator>:: // .
            call_and_return_vector_impl                         // .
            (TSelf&& self, Ts&&... xs)
        {
            std::vector<fn_return_type> result;
            result.reserve(self._functions.size());

            call_and_use_result_impl(FWD(self),
                [&result](auto&& x)
                {
                    result.emplace_back(FWD(x));
                },
                FWD(xs)...);

            return result;
        }

#define VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(qualifier)            \
    VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator) \
    template <typename TF, typename... Ts>                                  \
    auto base_delegate<TFunction, TSignature,                               \
        TAllocator>::call_and_use_result(TF&& result_handler, Ts&&... xs)   \
        qualifier noexcept(noexcept(call_and_use_result_impl(               \
            this_type{}, result_handler, FWD(xs)...)))                      \
    {                                                                       \
        return call_and_use_result_impl(*this, result_handler, FWD(xs)...); \
    }                                                                       \
                                                                            \
    VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator) \
    template <typename... Ts>                                               \
    auto base_delegate<TFunction, TSignature, TAllocator>::operator()(      \
        Ts && ... xs)                                                       \
        qualifier noexcept(noexcept(call_impl(this_type{}, FWD(xs)...)))    \
    {                                                                       \
        return call_impl(*this, FWD(xs)...);                                \
    }                                                                       \
                                                                            \
    VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator) \
    template <typename... Ts>                                               \
    auto base_delegate<TFunction, TSignature,                               \
        TAllocator>::call_and_return_vector(Ts&&... xs)                     \
        qualifier noexcept(                                                 \
            noexcept(call_and_return_vector_impl(this_type{}, FWD(xs)...))) \
    {                                                                       \
        return call_and_return_vector_impl(*this, FWD(xs)...);              \
    }

        VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(&)
        VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(const&)
        VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(&&)

#undef VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS

        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        void base_delegate<TFunction, TSignature, TAllocator>::reserve(sz_t x)
        {
            _functions.reserve(x);
        }

        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        void base_delegate<TFunction, TSignature, TAllocator>::clear() noexcept
        {
            _functions.clear();
        }

        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        auto base_delegate<TFunction, TSignature, TAllocator>::empty() const
            noexcept
        {
            return _functions.empty();
        }
    }
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE
