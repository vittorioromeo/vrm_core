// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/experimental/handle2/settings/settings.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle2
    {
        namespace aliases
        {
            template <typename TSettings>
            using handle_data_type = typename TSettings::handle_data_type;

            template <typename TSettings>
            using target_type = typename TSettings::target_type;

            template <typename TSettings>
            using counter_type = typename TSettings::counter_type;

            template <typename TSettings>
            using handle_type = typename TSettings::handle_type;
        }
    }
}
VRM_CORE_NAMESPACE_END
