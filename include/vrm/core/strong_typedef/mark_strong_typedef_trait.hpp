// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/assert/static_assert_macros.hpp>

#define VRM_CORE_STRONG_TYPEDEF_TRAIT(name)             \
    VRM_CORE_NAMESPACE                                  \
    {                                                   \
        template <>                                     \
        struct is_strong_typedef<name> : std::true_type \
        {                                               \
        };                                              \
    }                                                   \
    VRM_CORE_NAMESPACE_END                              \
                                                        \
    VRM_CORE_STATIC_ASSERT_NM(::vrm::core::is_strong_typedef<name>{})
