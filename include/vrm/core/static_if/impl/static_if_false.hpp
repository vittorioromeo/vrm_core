// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

// Adapted from:
// https://github.com/isocpp/CppCoreGuidelines/issues/353

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/static_if/impl/static_if_impl.hpp>
#include <vrm/core/static_if/impl/static_if_result.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <>
        struct static_if_<false>
        {
            template <typename F>
            VRM_CORE_ALWAYS_INLINE auto& then(F&&)
            {
                // Ignore `then`, as the predicate is false.

                return *this;
            }

            template <typename F>
            VRM_CORE_ALWAYS_INLINE auto else_(F&& f) noexcept
            {
                // Assuming that `else_` is after all `else_if` calls.

                // We found a matching branch, just make a result and ignore
                // everything else.

                return make_static_if_result(FWD(f));
            }

            template <typename TPredicate>
            VRM_CORE_ALWAYS_INLINE auto else_if(TPredicate) noexcept
            {
                return make_static_if(TPredicate{});
            }

            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE auto operator()(Ts&&...) noexcept
            {
                // If there are no `else` branches, we must ignore a call to a
                // failed static if matching.
            }
        };
    }
}
VRM_CORE_NAMESPACE_END