// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T, typename TStorage>
        struct sparse_set_settings
        {
            VRM_CORE_STATIC_ASSERT_NM(
                is_strong_typedef_v<T> ||
                (std::is_arithmetic<T>{} && std::is_unsigned<T>{}));

            /// @brief Size type used for storage sizes/capacities.
            using size_type = sz_t;

            /// @brief Type of values stored in the sparse set.
            using value_type = T;

            /// @brief Type of storage.
            using storage_type = TStorage;
        };
    }
}
VRM_CORE_NAMESPACE_END
