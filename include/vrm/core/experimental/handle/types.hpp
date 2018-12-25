// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/experimental/handle/impl/settings.hpp>
#include <vrm/core/experimental/handle/manager.hpp>
#include <vrm/core/experimental/handle/strategy.hpp>

namespace vrm::core
{
    namespace handle
    {
        namespace impl
        {
            template <typename TSettings, sz_t TCount>
            using array_manager =          // .
                manager<                   // .
                    strategy::storage<     // .
                        TSettings,         // .
                        storage::hs_array< // .
                            TSettings,     // .
                            TCount>        // .
                        >                  // .
                    >;                     // .

            template <typename TSettings>
            using vector_manager =          // .
                manager<                    // .
                    strategy::storage<      // .
                        TSettings,          // .
                        storage::hs_vector< // .
                            TSettings       // .
                            >               // .
                        >                   // .
                    >;                      // .

            template <                     // .
                typename TSettings,        // .
                typename TMetadataRefType, // .
                typename TCustomGetters    // .
                >
            using custom_manager =        // .
                manager<                  // .
                    strategy::custom<     // .
                        TSettings,        // .
                        TMetadataRefType, // .
                        TCustomGetters    // .
                        >                 // .
                    >;                    // .
        }

        template <             // .
            typename TTarget,  // .
            typename TCounter, // .
            sz_t TCount        // .
            >
        using array_manager = impl::array_manager< // .
            settings<TTarget, TCounter>,           // .
            TCount                                 // .
            >;

        template <            // .
            typename TTarget, // .
            typename TCounter // .
            >
        using vector_manager = impl::vector_manager< // .
            settings<TTarget, TCounter>              // .
            >;                                       // .

        template <                     // .
            typename TTarget,          // .
            typename TCounter,         // .
            typename TMetadataRefType, // .
            typename TTargetGetter,    // .
            typename TCounterGetter    // .
            >
        using custom_manager = impl::custom_manager<             // .
            settings<TTarget, TCounter>,                         // .
            TMetadataRefType,                                    // .
            strategy::custom_getters<                            // .
                TMetadataRefType, TTargetGetter, TCounterGetter> // .
            >;
    }
}
