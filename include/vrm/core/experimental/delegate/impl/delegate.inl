// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/experimental/delegate/base_delegate.hpp>
#include <vrm/core/experimental/delegate/impl/delegate.hpp>

#define VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(function, signature, allocator) \
    template <template <typename...> class function, typename signature,     \
        typename allocator>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        template <typename TF>
        void delegate<TFunction, TSignature, TAllocator>::operator+=(TF&& f)
        {
            this->emplace_function(FWD(f));
        }
    }
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE
