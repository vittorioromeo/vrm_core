// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/experimental/sparse_set/base_sparse_set.hpp>

VRM_CORE_NAMESPACE
{
    /// @brief Sparse integer set, with fixed array storage.
    /// @details The storage is allocated inside the sparse set.
    template <typename T, sz_t TCapacity>
    using fixed_array_sparse_set = impl::base_sparse_set<       // .
        impl::sparse_set_settings<                              // .
            T,                                                  // .
            impl::sparse_set_storage::fixed_array<T, TCapacity> // .
            >                                                   // .
        >;

    /// @brief Sparse integer set, with fixed vector storage.
    /// @details The storage is allocated using an allocator.
    template <                                         // .
        typename T,                                    // .
        sz_t TCapacity,                                // .
        typename TDenseAllocator = std::allocator<T>,  // .
        typename TSparseAllocator = std::allocator<T*> // .
        >
    using fixed_vector_sparse_set = impl::base_sparse_set< // .
        impl::sparse_set_settings<                         // .
            T,                                             // .
            impl::sparse_set_storage::fixed_vector<        // .
                T,                                         // .
                TCapacity,                                 // .
                TDenseAllocator,                           // .
                TSparseAllocator                           // .
                >                                          // .
            >                                              // .
        >;

    /// @brief Sparse integer set, with dynamic (auto-resizing) vector storage.
    /// @details The storage is allocated using an allocator.
    template <                                           // .
        typename T,                                      // .
        typename TDenseAllocator = std::allocator<T>,    // .
        typename TSparseAllocator = std::allocator<sz_t> // .
        >
    using dynamic_vector_sparse_set = impl::base_sparse_set< // .
        impl::sparse_set_settings<                           // .
            T,                                               // .
            impl::sparse_set_storage::dynamic_vector<        // .
                T,                                           // .
                TDenseAllocator,                             // .
                TSparseAllocator                             // .
                >                                            // .
            >                                                // .
        >;
}
VRM_CORE_NAMESPACE_END
