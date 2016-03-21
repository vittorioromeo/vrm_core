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
            template <                                             // .
                typename T,                                        // .
                typename TDenseAllocator = ::std::allocator<T>,    // .
                typename TSparseAllocator = ::std::allocator<sz_t> // .
                >
            class dynamic_vector
            {
            public:
                using value_type = T;
                using sparse_type = sz_t;
                using dense_allocator_type = TDenseAllocator;
                using sparse_allocator_type = TSparseAllocator;

                static constexpr sparse_type null_idx =
                    std::numeric_limits<sparse_type>::max();

            private:
                multi_resizable_buffer<                                  // .
                    resizable_buffer<value_type, dense_allocator_type>,  // .
                    resizable_buffer<sparse_type, sparse_allocator_type> // .
                    > _buffers;

                sparse_type _size;
                sz_t _capacity{0};

                void grow_by(sz_t amount)
                {
                    auto new_capacity(_capacity + amount);
                    _buffers.grow(_capacity, new_capacity);

                    for(sz_t i(_capacity); i < new_capacity; ++i)
                    {
                        sparse()[i] = null_idx;
                    }

                    _capacity = new_capacity;
                }

                auto& dense() noexcept
                {
                    return _buffers.template nth_buffer<0>();
                }

                auto& sparse() noexcept
                {
                    return _buffers.template nth_buffer<1>();
                }

                const auto& dense() const noexcept
                {
                    return _buffers.template nth_buffer<0>();
                }

                const auto& sparse() const noexcept
                {
                    return _buffers.template nth_buffer<1>();
                }

                auto last_element_index() noexcept
                {
                    return _size - 1;
                }

                auto last_element_index() const noexcept
                {
                    return _size - 1;
                }

            public:
                dynamic_vector()
                {
                    grow_by(64);
                    _size = 0;
                }

                ~dynamic_vector()
                {
                    // TODO: _buffers.moved() ?
                    if(dense().data() != nullptr)
                    {
                        _buffers.destroy_and_deallocate(_capacity);
                    }
                }

                dynamic_vector(const dynamic_vector& rhs)
                    : _buffers{rhs._buffers.copy(rhs._size)}, _size{rhs._size}
                {
                }

                dynamic_vector& operator=(const dynamic_vector& rhs)
                {
                    _buffers = rhs._buffers.copy(rhs._size);
                    _size = rhs._size;

                    return *this;
                }

                dynamic_vector(dynamic_vector&&) = default;
                dynamic_vector& operator=(dynamic_vector&&) = default;

                void clear() noexcept
                {
                    for(sz_t i(0); i < _capacity; ++i)
                    {
                        sparse()[i] = null_idx;
                    }

                    _size = 0;
                }

                bool has(const T& x) const noexcept
                {
                    if(x >= _capacity)
                    {
                        return false;
                    }

                    return sparse()[x] != null_idx;
                }

                void grow_if_required()
                {
                    if(size() < _capacity) return;
                    grow_by(_capacity);
                }

                bool add(const T& x)
                {
                    if(has(x)) return false;
                    grow_if_required();

                    VRM_CORE_ASSERT_OP(size(), <, _capacity);
                    dense()[_size] = x;

                    sparse()[x] = _size;
                    ++_size;

                    return true;
                }

                bool erase(const T& x) noexcept
                {
                    if(!has(x)) return false;

                    auto idx(sparse()[x]);
                    VRM_CORE_ASSERT_OP(size(), >, 0);

                    auto last(back());
                    VRM_CORE_ASSERT_OP(idx, !=, null_idx);

                    auto& val(dense()[idx]);

                    if(val != last)
                    {
                        val = last;
                        sparse()[last] = idx;
                    }

                    VRM_CORE_ASSERT(has(x));
                    sparse()[x] = null_idx;

                    VRM_CORE_ASSERT_OP(size(), >, 0);
                    --_size;

                    return true;
                }


                bool empty() const noexcept
                {
                    return _size == 0;
                }

                // TODO: bool
                void pop_back() noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), >, 0);
                    erase(back());
                }

                auto back() const noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), >, 0);

                    VRM_CORE_ASSERT(has(dense()[last_element_index()]));
                    return dense()[last_element_index()];
                }

                template <typename TF>
                void for_each(TF&& f) const noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), <=, _capacity);

                    for(sz_t i(0); i < _size; ++i)
                    {
                        VRM_CORE_ASSERT(has(dense()[i]));
                        f(dense()[i]);
                    }
                }

                auto size() const noexcept
                {
                    return _size;
                }

                auto begin() noexcept
                {
                    return dense().data();
                }

                auto begin() const noexcept
                {
                    return static_cast<const T*>(dense().data());
                }

                auto end() noexcept
                {
                    return dense().data() + _size;
                }

                auto end() const noexcept
                {
                    return static_cast<const T*>(dense().data() + _size);
                }

                auto& operator[](sz_t i) noexcept
                {
                    VRM_CORE_ASSERT_OP(i, <, size());
                    return dense()[i];
                }

                const auto& operator[](sz_t i) const noexcept
                {
                    VRM_CORE_ASSERT_OP(i, <, size());
                    return dense()[i];
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
