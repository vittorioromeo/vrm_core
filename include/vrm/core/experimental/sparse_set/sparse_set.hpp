// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/experimental/sparse_set/base_sparse_set.hpp>
#include <vrm/core/config.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T, sz_t TCapacity>
    using fixed_array_sparse_set = impl::base_sparse_set<       // .
        impl::sparse_set_settings<                              // .
            T,                                                  // .
            impl::sparse_set_storage::fixed_array<T, TCapacity> // .
            >                                                   // .
        >;

    template <typename T, sz_t TCapacity>
    using fixed_vector_sparse_set = impl::base_sparse_set<       // .
        impl::sparse_set_settings<                               // .
            T,                                                   // .
            impl::sparse_set_storage::fixed_vector<T, TCapacity> // .
            >                                                    // .
        >;

    template <typename T>
    using dynamic_vector_sparse_set = impl::base_sparse_set< // .
        impl::sparse_set_settings<                           // .
            T,                                               // .
            impl::sparse_set_storage::dynamic_vector<T>      // .
            >                                                // .
        >;
}
VRM_CORE_NAMESPACE_END
