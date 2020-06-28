// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/assert/assert_macros.hpp>
#include <vrm/core/assert/assert_macros_interface.hpp>
#include <vrm/core/config.hpp>

#if !VRM_CORE_IMPL_ASSERT_DISABLED

#include <vrm/core/assert/impl/assert.hpp>
#include <vrm/core/assert/impl/assert.inl>

#if defined(VRM_CORE_INLINE_LIBRARY)
#include <vrm/core/assert/impl/assert.cpp>
#endif

#endif
