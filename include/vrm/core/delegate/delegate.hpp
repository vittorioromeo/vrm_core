// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/delegate/base_delegate.hpp>

// TODO: WIP
// * templatize fn_type
// * templatize container
// ** fixed_delegate<10>
// ** fixed_unsubscribable_delegate<10>
// ** delegate
// ** unsubscribable_delegate

VRM_CORE_NAMESPACE
{
    template <typename>
    class VRM_CORE_CLASS_API delegate;

    template <typename TReturn, typename... TArgs>
    class VRM_CORE_CLASS_API delegate<TReturn(TArgs...)>
        : public impl::base_delegate<TReturn(TArgs...)>
    {
    private:
        using base_type = impl::base_delegate<TReturn(TArgs...)>;

    public:
        using fn_type = typename base_type::fn_type;

    public:
        template <typename TF>
        void operator+=(TF&& f)
        {
            this->emplace_function(FWD(f));
        }
    };
}
VRM_CORE_NAMESPACE_END