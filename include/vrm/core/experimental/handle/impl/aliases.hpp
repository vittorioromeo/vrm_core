// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once


namespace vrm::core
{
    namespace handle
    {
        namespace impl
        {
            template <typename T>
            using target_type = typename T::target_type;

            template <typename T>
            using counter_type = typename T::counter_type;

            template <typename T>
            using metadata_type = typename T::metadata_type;

            template <typename T>
            using metadata_ref_type = typename T::metadata_ref_type;

            template <typename T, typename TMetadataRef>
            using handle_type = typename T::template handle_type<TMetadataRef>;
        } // namespace impl
    }     // namespace handle
} // namespace vrm::core
