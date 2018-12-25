// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/assert/assert_macros.hpp>
#include <vrm/core/assert/assert_macros_interface.hpp>
#include <vrm/core/config.hpp>

#if !VRM_CORE_IMPL_ASSERT_DISABLED

namespace vrm::core::impl::assert
{
    /// @brief Assertion management state.
    /// @details Controls whether or not future assertion will be
    /// skipped.
    struct state final
    {
        bool _skip{false};
    };

    /// @brief Returns a reference to the thread-local assertion state.
    state& get_state() noexcept;

    /// @brief Fires an assertion failure.
    template <typename TLhs, typename TRhs>
    void fire(const char* code, const char* line, const char* file,
        const char* lhs, const char* op, const char* rhs, const char* msg,
        const TLhs& lhs_res, const TRhs& rhs_res);
} // namespace vrm::core::impl::assert

#endif
