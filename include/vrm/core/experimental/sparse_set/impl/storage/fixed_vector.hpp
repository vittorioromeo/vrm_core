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
            template <                                           // .
                typename T,                                      // .
                sz_t TCapacity,                                  // .
                typename TDenseAllocator = ::std::allocator<T>,  // .
                typename TSparseAllocator = ::std::allocator<T*> // .
                >
            class fixed_vector
            {
            public:
                using value_type = T;
                using dense_allocator_type = TDenseAllocator;
                using sparse_allocator_type = TSparseAllocator;

                static constexpr auto capacity = TCapacity;

            private:
                multi_resizable_buffer<                         // .
                    resizable_buffer<T, dense_allocator_type>,  // .
                    resizable_buffer<T*, sparse_allocator_type> // .
                    > _buffers;

                T* _end;

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

                auto last_element_ptr() noexcept
                {
                    return _end - 1;
                }

                auto last_element_ptr() const noexcept
                {
                    return _end - 1;
                }

            public:
                fixed_vector()
                {
                    _buffers.grow(0, capacity);
                    clear();
                }

                ~fixed_vector()
                {
                    // TODO: _buffers.moved() ?
                    if(dense().data() != nullptr)
                    {
                        _buffers.destroy_and_deallocate(capacity);
                    }
                }

                fixed_vector(const fixed_vector&) = delete;
                fixed_vector& operator=(const fixed_vector&) = delete;

                fixed_vector(fixed_vector&& rhs)
                {
                    auto temp_size = rhs.size();
                    std::cout << "ts: " << temp_size << std::endl;

                    _buffers = std::move(rhs._buffers);
                    _end = dense().data() + temp_size;
                }
                fixed_vector& operator=(fixed_vector&& rhs)
                {
                    auto temp_size = rhs.size();
                    std::cout << "ts: " << temp_size << std::endl;

                    _buffers = std::move(rhs._buffers);
                    _end = dense().data() + temp_size;

                    return *this;
                }

                void clear() noexcept
                {
                    for(sz_t i(0); i < capacity; ++i)
                    {
                        sparse()[i] = nullptr;
                    }

                    _end = dense().data();
                }

                bool has(const T& x) const noexcept
                {
                    VRM_CORE_ASSERT_OP(x, <, capacity);
                    return sparse()[x] != nullptr;
                }

                bool add(const T& x) noexcept
                {
                    VRM_CORE_ASSERT_OP(x, <, capacity);
                    if(has(x)) return false;

                    VRM_CORE_ASSERT_OP(size(), <, capacity);
                    *_end = x;

                    sparse()[x] = _end;
                    ++_end;

                    return true;
                }

                bool erase(const T& x) noexcept
                {
                    VRM_CORE_ASSERT_OP(x, <, capacity);
                    if(!has(x)) return false;

                    auto& ptr(sparse()[x]);
                    VRM_CORE_ASSERT_OP(size(), >, 0);

                    auto last(back());
                    VRM_CORE_ASSERT_OP(ptr, !=, nullptr);

                    if(*ptr != last)
                    {
                        *ptr = last;
                        sparse()[last] = ptr;
                    }

                    VRM_CORE_ASSERT(has(x));
                    ptr = nullptr;

                    VRM_CORE_ASSERT_OP(size(), >, 0);
                    --_end;

                    return true;
                }


                bool empty() const noexcept
                {
                    return _end == dense().data();
                }

                void pop_back() noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), >, 0);
                    erase(back());
                }

                auto back() const noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), >, 0);

                    VRM_CORE_ASSERT(has(*(last_element_ptr())));
                    return *(last_element_ptr());
                }

                template <typename TF>
                void for_each(TF&& f) const noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), <=, capacity);

                    for(auto p(dense().data()); p != _end; ++p)
                    {
                        VRM_CORE_ASSERT(has(*p));
                        f(*p);
                    }
                }

                auto size() const noexcept
                {
                    std::cout << "start: " << (void*)begin() << std::endl;
                    std::cout << "end: " << (void*)end() << std::endl;
                    return to_sz_t(end() - begin());
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
                    return _end;
                }

                auto end() const noexcept
                {
                    return static_cast<const T*>(_end);
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
