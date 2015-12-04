// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

// Adapted from:
// https://github.com/isocpp/CppCoreGuidelines/issues/353

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/is_valid.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/type_traits.hpp>
#include <vrm/core/static_if/impl/static_if_impl.hpp>
#include <vrm/core/static_if/impl/static_if_true.hpp>
#include <vrm/core/static_if/impl/static_if_false.hpp>
#include <vrm/core/static_if/impl/static_if_result.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        auto is_valid_predicate(
            is_valid([](auto x) -> decltype(decltype(x)::value)
                {
                }));
    }

    template <typename TPredicate>
    VRM_CORE_ALWAYS_INLINE constexpr auto static_if(TPredicate) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(impl::is_valid_predicate(TPredicate{}));
        return impl::make_static_if(TPredicate{});
    }
}
VRM_CORE_NAMESPACE_END

/*
#define VRM_CORE_STATIC_IF(...) \
    ::vrm::core::static_if(::vrm::core::bool_v<__VA_ARGS__>)

#define VRM_CORE_THEN .then

#define VRM_CORE_ELSE_IF(...) \
    .else_if(::vrm::core::bool_v<__VA_ARGS__>)
*/
