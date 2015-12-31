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

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <template <typename...> class TFunction, typename TSignature>
        using default_delegate_allocator =
            ::std::allocator<TFunction<TSignature>>;

        template <template <typename...> class TFunction, typename TSignature,
            typename TAllocator =
                default_delegate_allocator<TFunction, TSignature>>
        struct delegate_settings
        {
            using fn_signature = TSignature;
            using fn_type = TFunction<fn_signature>;
            using fn_return_type = signature_return_type<TSignature>;
            using allocator_type = TAllocator;
            using allocator_traits = ::std::allocator_traits<allocator_type>;
            using fn_vector_type = ::std::vector<fn_type, allocator_type>;
        };

        template <typename TSettings>
        class VRM_CORE_CLASS_API base_delegate
        {
        private:
            using settings_type = TSettings;

        protected:
            using fn_signature = typename settings_type::fn_signature;

        private:
            using this_type = base_delegate<TSettings>;

        public:
            using allocator_type = typename settings_type::allocator_type;
            using fn_type = typename settings_type::fn_type;
            using fn_return_type = typename settings_type::fn_return_type;
            using fn_vector_type = typename settings_type::fn_vector_type;

        protected:
            fn_vector_type _functions;

            template <typename TF>
            void emplace_function(TF&& f);

            template <typename TSelf, typename TF, typename... Ts>
            static void call_and_use_result_impl                // .
                (TSelf&& self, TF&& result_handler, Ts&&... xs) // .
                noexcept(
                    noexcept(result_handler(self._functions.back()(xs...))));

            template <typename TSelf, typename... Ts>
            static void call_impl(TSelf&& self, Ts&&... xs) // .
                noexcept(noexcept(self._functions.back()(xs...)));

            template <typename TSelf, typename... Ts>
            static auto call_and_return_vector_impl(TSelf&& self, Ts&&... xs);

        public:
            base_delegate() = default;

            base_delegate(const base_delegate&) = default;
            base_delegate& operator=(const base_delegate&) = default;

            base_delegate(base_delegate&&) = default;
            base_delegate& operator=(base_delegate&&) = default;

#define VRM_CORE_IMPL_DEFINE_DELEGATE_DEFINITIONS(qualifier)              \
    template <typename TF, typename... Ts>                                \
    auto call_and_use_result(TF&& result_handler, Ts&&... xs)             \
        qualifier noexcept(noexcept(call_and_use_result_impl(             \
            this_type{}, result_handler, FWD(xs)...)));                   \
                                                                          \
    template <typename... Ts>                                             \
    auto operator()(Ts && ... xs)                                         \
        qualifier noexcept(noexcept(call_impl(this_type{}, FWD(xs)...))); \
                                                                          \
    template <typename... Ts>                                             \
    auto call_and_return_vector(Ts&&... xs) qualifier noexcept(           \
        noexcept(call_and_return_vector_impl(this_type{}, FWD(xs)...)));

            VRM_CORE_IMPL_DEFINE_DELEGATE_DEFINITIONS(&)
            VRM_CORE_IMPL_DEFINE_DELEGATE_DEFINITIONS(const&)
            VRM_CORE_IMPL_DEFINE_DELEGATE_DEFINITIONS(&&)

#undef VRM_CORE_IMPL_DEFINE_DELEGATE_DEFINITIONS

            void reserve(sz_t x);
            void clear() noexcept;
            auto empty() const noexcept;
        };
    }
}
VRM_CORE_NAMESPACE_END
