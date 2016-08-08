// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/integral_constant.hpp>
#include <vrm/core/experimental/resource/base.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            template <typename TBehavior>
            class unique : public impl::base<TBehavior>
            {
            public:
                using this_type = unique<TBehavior>;
                using base_type = impl::base<TBehavior>;
                using behavior_type = typename base_type::behavior_type;
                using handle_type = typename base_type::handle_type;

            private:
                using is_nothrow_deinit = is_nothrow_deinit_t<TBehavior>;

            public:
                void reset() noexcept(is_nothrow_deinit{});
                void reset(const handle_type& handle) noexcept(
                    is_nothrow_deinit{});

                ~unique() noexcept(is_nothrow_deinit{});

                unique() noexcept = default;
                explicit unique(const handle_type& handle) noexcept;

                unique(const unique&) = delete;
                unique& operator=(const unique&) = delete;

                unique(unique&& rhs) noexcept;
                auto& operator=(unique&&) noexcept(is_nothrow_deinit{});

                auto release() noexcept;

                void swap(unique& rhs) noexcept;

                template <typename>
                friend bool operator==(
                    const unique& lhs, const unique& rhs) noexcept;

                template <typename>
                friend bool operator!=(
                    const unique& lhs, const unique& rhs) noexcept;

                template <typename>
                friend void swap(unique& lhs, unique& rhs) noexcept;
            };
        }

        using impl::unique;
    }
}
VRM_CORE_NAMESPACE_END
