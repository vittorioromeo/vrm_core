// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
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
                using base_type = impl::base<TBehavior>;
                using behavior_type = typename base_type::behavior_type;
                using handle_type = typename base_type::handle_type;

            public:
                unique() noexcept = default;
                ~unique() noexcept;

                explicit unique(const handle_type& handle) noexcept;

                unique(const unique&) = delete;
                unique& operator=(const unique&) = delete;

                unique(unique&& rhs) noexcept;
                auto& operator=(unique&&) noexcept;

                auto release() noexcept;

                void reset() noexcept;
                void reset(const handle_type& handle) noexcept;

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
