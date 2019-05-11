// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <vector>
#include <vrm/core/experimental/delegate/base_delegate.hpp>

// TODO: WIP
// * templatize fn_type
// * templatize container
// ** fixed_delegate<10>
// ** fixed_unsubscribable_delegate<10>
// ** delegate
// ** unsubscribable_delegate

namespace vrm::core
{
    namespace impl
    {
        template <typename TSettings>
        class VRM_CORE_CLASS_API delegate
            : public impl::base_delegate<TSettings>
        {
        private:
            using base_type = impl::base_delegate<TSettings>;
            using fn_signature = typename base_type::fn_signature;

        public:
            using fn_type = typename base_type::fn_type;

            delegate() = default;

            delegate(const delegate&) = default;
            delegate& operator=(const delegate&) = default;

            delegate(delegate&&) = default;
            delegate& operator=(delegate&&) = default;

            template <typename TF>
            void operator+=(TF&& f);
        };
    } // namespace impl

    template <typename TSignature,
        typename TAllocator =
            impl::default_delegate_allocator<std::function, TSignature>>
    using delegate = impl::delegate<
        impl::delegate_settings<std::function, TSignature, TAllocator>>;
} // namespace vrm::core
