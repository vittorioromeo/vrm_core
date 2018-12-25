// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <vrm/core/assert/assert_macros.hpp>
#include <vrm/core/config.hpp>

#if !VRM_CORE_IMPL_ASSERT_DISABLED

#include <vrm/core/assert/impl/assert.hpp>

namespace vrm::core
{
    namespace impl
    {
        namespace assert
        {
            VRM_CORE_FN_API state& VRM_CORE_CONST_FN get_state() noexcept
            {
                thread_local state result;
                return result;
            }
        }
    }
}

#endif
