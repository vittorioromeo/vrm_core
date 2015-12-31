// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        template <typename TTarget, typename TCounter>
        struct settings
        {
            // From metadata to target user-specified object.
            using target_type = TTarget;

            // Counter type (verifies handle validity).
            using counter_type = TCounter;

            struct metadata_type
            {
                target_type _target;
                counter_type _counter{0};
            };

            template <typename TMetadataRef>
            struct handle_type
            {
                TMetadataRef _metadata_ref;
                counter_type _counter{0};
            };
        };
    }
}
VRM_CORE_NAMESPACE_END
