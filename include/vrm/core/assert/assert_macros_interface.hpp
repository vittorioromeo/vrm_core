// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/assert/assert_macros.hpp>

#define VRM_CORE_ASSERT_OP_MSG(lhs, op, rhs, msg) \
    VRM_CORE_IMPL_ASSERT(lhs, op, rhs, msg)

#define VRM_CORE_ASSERT_OP(lhs, op, rhs) \
    VRM_CORE_ASSERT_OP_MSG(lhs, op, rhs, "")

#define VRM_CORE_ASSERT_MSG(expr, msg) \
    VRM_CORE_ASSERT_OP_MSG(expr, ==, true, msg)

#define VRM_CORE_ASSERT(expr) VRM_CORE_ASSERT_MSG(expr, "")



#define VRM_CORE_CONSTEXPR_ASSERT_OP_MSG(lhs, op, rhs, msg) \
    VRM_CORE_IMPL_CONSTEXPR_ASSERT(lhs, op, rhs, msg)

#define VRM_CORE_CONSTEXPR_ASSERT_OP(lhs, op, rhs) \
    VRM_CORE_CONSTEXPR_ASSERT_OP_MSG(lhs, op, rhs, "")

#define VRM_CORE_CONSTEXPR_ASSERT_MSG(expr, msg) \
    VRM_CORE_CONSTEXPR_ASSERT_OP_MSG(expr, ==, true, msg)

#define VRM_CORE_CONSTEXPR_ASSERT(expr) VRM_CORE_CONSTEXPR_ASSERT_MSG(expr, "")