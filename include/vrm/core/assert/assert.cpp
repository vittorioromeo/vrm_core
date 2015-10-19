// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <vrm/core/assert/assert.hpp>

#if !VRM_CORE_IMPL_ASSERT_DISABLED

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        namespace assert
        {
            VRM_CORE_API_INLINE state& get_state() noexcept
            {
                static state result;
                return result;
            }
        }
    }
}
VRM_CORE_NAMESPACE_END

#endif