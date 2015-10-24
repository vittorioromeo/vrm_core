// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename...>
        struct overload_set;

        template <typename TF>
        struct overload_set<TF> : TF
        {
            using call_type = TF;
            using call_type::operator();
        };

        template <typename TF, typename... TFs>
        struct overload_set<TF, TFs...> : TF, overload_set<TFs...>::call_type
        {
            using base_type = typename overload_set<TFs...>::call_type;

            using f_type = TF;
            using call_type = overload_set;

            VRM_CORE_ALWAYS_INLINE overload_set(TF &&f, TFs &&... fs) noexcept
                : f_type(FWD(f)),
                  base_type(FWD(fs)...)
            {
            }

            using f_type::operator();
            using base_type::operator();
        };
    }

    template <typename... TFs>
    VRM_CORE_ALWAYS_INLINE auto make_overload(TFs && ... fs) noexcept
    {
        return impl::overload_set<TFs...>{FWD(fs)...};
    }
}
VRM_CORE_NAMESPACE_END