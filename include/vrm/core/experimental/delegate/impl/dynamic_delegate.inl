// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/experimental/delegate/base_delegate.hpp>
#include <vrm/core/experimental/delegate/impl/dynamic_delegate.hpp>

#define VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(function, signature, allocator) \
    template <template <typename...> class function, typename signature,     \
        typename allocator>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        auto dynamic_delegate<TFunction, TSignature, TAllocator>::next_fn_idx()
            const noexcept
        {
            return this->_functions.size() - 1;
        }

        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        template <typename TF>
        auto dynamic_delegate<TFunction, TSignature, TAllocator>::operator+=(
            TF&& f)
        {
            // Emplace function at the end of functions vector.
            this->emplace_function(FWD(f));

            // Return an handle to it.
            return _hm.create(next_fn_idx());
        }

        VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE(TFunction, TSignature, TAllocator)
        void dynamic_delegate<TFunction, TSignature, TAllocator>::operator-=(
            const handle_type& h)
        {
            _hm.destroy(h, [this](auto i)
                {
                    // Swap dead function with last function in the vector.
                    std::swap(this->_functions[i], this->_functions.back());
                    this->_functions.pop_back();
                });
        }
    }
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_BASE_DELEGATE_TEMPLATE
