// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/experimental/delegate/base_delegate.hpp>

// TODO: WIP
// * templatize fn_type
// * templatize container
// ** fixed_delegate<10>
// ** fixed_unsubscribable_delegate<10>
// ** delegate
// ** unsubscribable_delegate

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <template <typename...> class TFunction, typename TSignature>
        class VRM_CORE_CLASS_API delegate
            : public impl::base_delegate<TFunction, TSignature>
        {
        private:
            using base_type = impl::base_delegate<TFunction, TSignature>;
            using fn_signature = typename base_type::fn_signature;

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

    template <typename TSignature>
    using delegate = impl::delegate<std::function, TSignature>;
}
VRM_CORE_NAMESPACE_END
