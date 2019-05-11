// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <vector>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/delegate/base_delegate.hpp>
#include <vrm/core/experimental/handle.hpp>
#include <vrm/core/strong_typedef.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

// TODO: WIP:
// * use sparse int set?

// TODO:
// Strong handle typedefs for index/target

namespace vrm::core
{
    namespace impl
    {
        template <typename TSettings>
        class VRM_CORE_CLASS_API dynamic_delegate
            : public impl::base_delegate<TSettings>
        {
        private:
            using handle_index_type = sz_t;
            using handle_counter_type = i8;

            using handle_settings_type =
                handle::settings<handle_index_type, handle_counter_type>;

            using base_type = impl::base_delegate<TSettings>;
            using allocator_type = typename base_type::allocator_type;

            // TODO: propagate allocator properly?
            using handle_storage_type =
                handle::storage::hs_vector<handle_settings_type>;

            using handle_manager_type =
                handle::manager<handle::strategy::storage<handle_settings_type,
                    handle_storage_type>>;

            using handle_type = typename handle_manager_type::handle_type;


            handle_manager_type _hm;

            auto next_fn_idx() const noexcept;

        public:
            using fn_type = typename base_type::fn_type;

            dynamic_delegate() = default;

            dynamic_delegate(const dynamic_delegate&) = default;
            dynamic_delegate& operator=(const dynamic_delegate&) = default;

            dynamic_delegate(dynamic_delegate&&) = default;
            dynamic_delegate& operator=(dynamic_delegate&&) = default;

            template <typename TF>
            auto operator+=(TF&& f);

            void operator-=(const handle_type& h);

            // TODO: clear/reserve hm
        };
    } // namespace impl

    template <typename TSignature,
        typename TAllocator =
            impl::default_delegate_allocator<std::function, TSignature>>
    using dynamic_delegate = impl::dynamic_delegate<
        impl::delegate_settings<std::function, TSignature, TAllocator>>;
} // namespace vrm::core
