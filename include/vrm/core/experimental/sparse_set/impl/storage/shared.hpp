// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases.hpp>
#include <vrm/core/casts.hpp>
#include <vrm/core/experimental/resizable_buffer.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        namespace sparse_set_storage
        {
            class utils
            {
            private:
                template <typename TSparseSetStorage, typename T>
                void nullify_and_decrement(TSparseSetStorage& s, T x) noexcept
                {
                    VRM_CORE_ASSERT(s.has(x));

                    // Nullify the old reference to `x`.
                    s.nullify(x);

                    // Decrement the size of the set and return `true`.
                    s.decrement_size();
                }

                template <typename TSparseSetStorage, typename T>
                void unchecked_add(TSparseSetStorage& s, T x) // .
                    noexcept(noexcept(                        // .
                        s.grow_if_required(x)                 // .
                        ))
                {
                    // Grows the storage if possible and required.
                    s.grow_if_required(x);

                    // Assert the capacity is big enough.
                    VRM_CORE_ASSERT_OP(s.size(), <, s.capacity());

                    // Set last dense and sparse element and return.
                    s.set_last_element(x);
                }

                template <typename TSparseSetStorage, typename T>
                void unchecked_erase(TSparseSetStorage& s, T x) noexcept
                {
                    VRM_CORE_ASSERT_OP(s.size(), >, 0);
                    VRM_CORE_ASSERT(s.has(x));

                    // Get the "sparse reference" for `x`.
                    auto x_ref(s.sparse()[x]);
                    VRM_CORE_ASSERT(!s.is_null(x_ref));

                    // Get the last element in the set.
                    auto last(s.back());

                    // Get the value by following `x`'s sparse reference.
                    auto& val(s.value_from_sparse(x_ref));

                    // If the value to erase is not the last value in the set...
                    if(val != last)
                    {
                        // ...swap the value in the position `x_ref` with the
                        // last value...
                        val = last;

                        // ...and update the last sparse reference.
                        s.sparse()[last] = x_ref;
                    }

                    nullify_and_decrement(s, x);
                }

            public:
                template <typename TSparseSetStorage, typename T>
                bool add_impl(TSparseSetStorage& s, T x) // .
                    noexcept(noexcept(                   // .
                        s.grow_if_required(x)            // .
                        ))
                {
                    if(s.has(x))
                    {
                        // If `x` is already in the set, return `false`.
                        return false;
                    }

                    unchecked_add(s, x);
                    return true;
                }

                template <typename TSparseSetStorage, typename T>
                bool erase_impl(TSparseSetStorage& s, T x) noexcept
                {
                    if(!s.has(x))
                    {
                        // If `x` is not in the set, return `false`.
                        return false;
                    }

                    unchecked_erase(s, x);
                    return true;
                }

                template <typename TSparseSetStorage>
                void pop_back_impl(TSparseSetStorage& s) noexcept
                {
                    VRM_CORE_ASSERT_OP(s.size(), >, 0);
                    nullify_and_decrement(s, s.back());
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
