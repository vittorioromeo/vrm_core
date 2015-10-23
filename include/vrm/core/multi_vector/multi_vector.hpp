// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <memory>
#include <tuple>
#include <vrm/core/internal.hpp>
#include <vrm/core/detection.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/resizable_buffer.hpp>
#include <vrm/core/tuple_utils.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T, typename TAllocator = ::std::allocator<T>>
        struct multi_vector_buffer
        {
            using value_type = T;
            using allocator_type = TAllocator;
            using resizable_buffer_type = resizable_buffer<T, TAllocator>;

            resizable_buffer_type _resizable_buffer;

            multi_vector_buffer() = default;

            multi_vector_buffer(const TAllocator& allocator)
                : _resizable_buffer(allocator)
            {
            }

            multi_vector_buffer(const multi_vector_buffer&) = default;
            multi_vector_buffer& operator=(
                const multi_vector_buffer&) = default;

            multi_vector_buffer(multi_vector_buffer&&) = default;
            multi_vector_buffer& operator=(multi_vector_buffer&&) = default;
        };

        template <typename... TBufferTypes>
        class multi_vector
        {
            VRM_CORE_STATIC_ASSERT_NM(sizeof...(TBufferTypes) > 0);

        public:
            using size_type = std::size_t;
            static constexpr size_type initial_capacity{0};

            using value_reference_tuple =
                std::tuple<typename TBufferTypes::value_type&...>;

            using const_value_reference_tuple =
                std::tuple<const typename TBufferTypes::value_type&...>;

        private:
            std::tuple<TBufferTypes...> _buffers;
            size_type _capacity{0};
            size_type _size{0};

            template <typename TF>
            VRM_CORE_ALWAYS_INLINE void for_buffers(TF&& f)
            {
                for_tuple(
                    [&f](auto& bx)
                    {
                        f(bx._resizable_buffer);
                    },
                    _buffers);
            }

            void grow_if_necessary(size_type desired_size)
            {
                if(desired_size > _capacity)
                {
                    reserve((_capacity + 10) * 2);
                }
            }


        public:
            multi_vector() = default;

            ~multi_vector()
            {
                for_buffers([this](auto& b)
                    {
                        b.destroy(_size);
                        b.deallocate(_capacity);
                    });
            }

            multi_vector(const multi_vector&) = default;
            multi_vector& operator=(const multi_vector&) = default;

            multi_vector(multi_vector&&) = default;
            multi_vector& operator=(multi_vector&&) = default;

            const auto& size() const noexcept { return _size; }
            const auto& capacity() const noexcept { return _capacity; }
            auto empty() const noexcept { return _size == 0; }

            void reserve(size_type new_capacity)
            {
                VRM_CORE_ASSERT_OP(new_capacity, >, _capacity);

                for_buffers([this, &new_capacity](auto& b)
                    {
                        b.grow(_capacity, new_capacity);
                    });

                _capacity = new_capacity;
            }

            void resize(size_type new_size)
            {
                VRM_CORE_ASSERT_OP(new_size, >, _size);
                grow_if_necessary(new_size);

                for_buffers([this, &new_size](auto& b)
                    {
                        for(size_type i(_size); i < new_size; ++i)
                        {
                            b.construct_at(i);
                        }
                    });

                _size = new_size;
            }

            void clear()
            {
                for_buffers([this](auto& b)
                    {
                        b.destroy(_size);
                    });

                _size = 0;
            }

            void insert() {}
            void emplace() {}
            void erase() {}

            void push_back() {}
            void emplace_back() {}
            void pop_back() {}

            auto operator[](size_type pos) noexcept
            {
                return value_reference_tuple{
                    std::get<TBufferTypes>(_buffers)._resizable_buffer[pos]...};
            }

            auto operator[](size_type pos) const noexcept
            {
                return const_value_reference_tuple{
                    std::get<TBufferTypes>(_buffers)._resizable_buffer[pos]...};
            }
        };
    }
}
VRM_CORE_NAMESPACE_END
