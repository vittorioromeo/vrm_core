// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config/names.hpp>
#include <vrm/core/assert/static_assert_macros.hpp>
#include <vrm/core/strong_typedef.hpp>

VRM_CORE_NAMESPACE
{
    namespace handle
    {
        /// @brief Compile-time settings for handle storage.
        template <typename TTarget, typename TCounter>
        struct settings
        {
            // TODO: traits
            VRM_CORE_STATIC_ASSERT_NM(
                is_strong_typedef_v<TTarget> ||
                (std::is_arithmetic<TTarget>{} && std::is_unsigned<TTarget>{}));

            VRM_CORE_STATIC_ASSERT_NM( // .
                is_strong_typedef_v<TCounter> ||
                std::is_arithmetic<TCounter>{});

            /// @brief Points from metadata to target user-specified object.
            /// @details Stored inside metadata instances in the storage.
            using target_type = TTarget;

            /// @brief Counter type (verifies handle validity).
            using counter_type = TCounter;

            /// @brief Handle metadata. Stored in the storage.
            /// @details Every handle points to a metadata instance. Every
            /// metadata instance points to a target.
            struct metadata_type
            {
                target_type _target;
                counter_type _counter{0};
            };

            /// @brief Lightweight handle that points to a metadata instance.
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
