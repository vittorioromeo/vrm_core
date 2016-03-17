// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle2
    {
        /// @brief Settings for an handle context.
        /// @tparam THandleData Type of data stored inside the handles. Usually
        /// an index that points to the desired real data.
        /// @tparam TTarget Type of data retrieved by accessing the handles.
        /// @tparam TCounter Type of validity counter.
        template <                // .
            typename THandleData, // .
            typename TTarget,     // .
            typename TCounter     // .
            >
        class settings
        {
        public:
            using handle_data_type = THandleData;
            using target_type = TTarget;
            using counter_type = TCounter;

            struct handle_type
            {
                handle_data_type _data;
                counter_type _counter{0};
            };
        };
    }
}
VRM_CORE_NAMESPACE_END
