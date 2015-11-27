// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/assert/static_assert_macros.hpp>
#include <vrm/core/assert/assert_macros.hpp>
#include <vrm/core/assert/assert_macros_interface.hpp>

#if !VRM_CORE_IMPL_ASSERT_DISABLED

#include <string>
#include <sstream>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        namespace assert
        {
            struct state
            {
                bool _skip{false};
            };

            state& get_state() noexcept;

            template <typename TLhs, typename TRhs>
            void fire(const char* code, const char* line, const char* file,
                const char* lhs, const char* op, const char* rhs,
                const char* msg, const TLhs& lhs_res, const TRhs& rhs_res);
        }
    }
}
VRM_CORE_NAMESPACE_END

#include <vrm/core/assert/assert.inl>

#if defined(VRM_CORE_INLINE_LIBRARY)
#include <vrm/core/assert/assert.cpp>
#endif

#else

VRM_CORE_NAMESPACE {}
VRM_CORE_NAMESPACE_END

#endif
