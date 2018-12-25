// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros/fwd.hpp>
#include <vrm/core/experimental/resource/unique.hpp>
#include <vrm/core/experimental/resource/shared.hpp>

namespace vrm::core
{
    namespace resource
    {
        namespace impl
        {
            template <template <typename> class TResource, typename TBehavior>
            class resource_maker
            {
            public:
                using behavior_type = TBehavior;
                using resource_type = TResource<behavior_type>;

            private:
                template <typename... Ts>
                decltype(auto) init_resource(Ts&&... xs) noexcept(
                    noexcept(true))
                {
                    return behavior_type::init(FWD(xs)...);
                }

            public:
                template <typename... Ts>
                auto operator()(Ts&&... xs) noexcept(noexcept(true))
                {
                    return resource_type{init_resource(FWD(xs)...)};
                }
            };
        }

        template <template <typename> class TResource, typename TBehavior,
            typename... Ts>
        auto make_resource(Ts&&... xs) noexcept(noexcept(true))
        {
            return impl::resource_maker<TResource, TBehavior>{}(FWD(xs)...);
        }

        template <typename TBehavior, typename... Ts>
        auto make_unique_resource(Ts&&... xs) noexcept(noexcept(true))
        {
            return make_resource<resource::unique, TBehavior>(FWD(xs)...);
        }

        template <typename TBehavior, typename... Ts>
        auto make_shared_resource(Ts&&... xs) noexcept(noexcept(true))
        {
            return make_resource<resource::shared, TBehavior>(FWD(xs)...);
        }
    }
}

// TODO: test, docs, split into inl
