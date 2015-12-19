// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <vrm/core/assert/assert_macros.hpp>

#if !VRM_CORE_IMPL_ASSERT_DISABLED

#include <vrm/core/assert/impl/assert.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        namespace assert
        {
            state& get_state() noexcept
            {
                thread_local state result;
                return result;
            }
        }
    }
}
VRM_CORE_NAMESPACE_END

#endif
