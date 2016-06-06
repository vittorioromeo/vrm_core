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
        /// @brief Compile-time settings for handle manager.
        template <typename TTarget, typename TCounter>
        class settings
        {
        private:
            using target_underlying_type =
                underlying_if_strong_typedef_type<TTarget>;

            using counter_underlying_type =
                underlying_if_strong_typedef_type<TCounter>;

            VRM_CORE_STATIC_ASSERT_NM(
                std::is_arithmetic<target_underlying_type>{} &&
                std::is_unsigned<target_underlying_type>{});

            VRM_CORE_STATIC_ASSERT_NM( // .
                std::is_arithmetic<counter_underlying_type>{});

        public:
            /// @brief Points from metadata to target user-specified object.
            using target_type = TTarget;

            /// @brief Counter type (checks handle validity).
            using counter_type = TCounter;

            /// @brief Lightweight handle that points to strategy-defined
            /// metadata and stores a counter.
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
