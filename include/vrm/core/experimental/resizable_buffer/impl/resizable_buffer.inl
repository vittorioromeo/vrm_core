// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <memory>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/static_if.hpp>
#include <vrm/core/experimental/resizable_buffer/impl/resizable_buffer.hpp>
#include <vrm/core/ostream_utils/nullptr_printer.hpp>

VRM_CORE_NAMESPACE
{
    template <typename T, typename TAllocator>
    void resizable_buffer<T, TAllocator>::construct_at(size_type idx)
    {
        allocator_traits::construct(_allocator, _data + idx);
    }

    template <typename T, typename TAllocator>
    void resizable_buffer<T, TAllocator>::destroy_at(size_type idx)
    {
        allocator_traits::destroy(_allocator, _data + idx);
    }


    template <typename T, typename TAllocator>
    VRM_CORE_ALWAYS_INLINE void swap(resizable_buffer<T, TAllocator> & lhs,
        resizable_buffer<T, TAllocator> & rhs) noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }

    template <typename T, typename TAllocator>
    void resizable_buffer<T, TAllocator>::swap(resizable_buffer & rhs) noexcept
    {
        using std::swap;

        swap(_allocator, rhs._allocator);
        swap(_data, rhs._data);
    }

    template <typename T, typename TAllocator>
    void resizable_buffer<T, TAllocator>::destroy(size_type from, size_type to)
    {
#if VRM_CORE_DEBUG
        if(to - from > 0)
        {
            VRM_CORE_ASSERT_OP(_data, !=, nullptr);
        }
#endif

        for(auto i(from); i < to; ++i)
        {
            destroy_at(i);
        }
    }

    template <typename T, typename TAllocator>
    void resizable_buffer<T, TAllocator>::deallocate(size_type n)
    {
        allocator_traits::deallocate(_allocator, _data, n);

#if VRM_CORE_DEBUG
        _data = nullptr;
#endif
    }

    template <typename T, typename TAllocator>
    void resizable_buffer<T, TAllocator>::destroy_and_deallocate(size_type n)
    {
        destroy(0, n);
        deallocate(n);
    }

    template <typename T, typename TAllocator>
    resizable_buffer<T, TAllocator>::resizable_buffer(
        const TAllocator& allocator)
        : _allocator{allocator}
    {
    }

    template <typename T, typename TAllocator>
    resizable_buffer<T, TAllocator>::resizable_buffer(
        resizable_buffer && rhs) noexcept
        : _allocator{std::move(rhs._allocator)},
          _data{std::move(rhs._data)}
    {
        rhs._data = nullptr;
    }

    template <typename T, typename TAllocator>
    resizable_buffer<T, TAllocator>& resizable_buffer<T, TAllocator>::operator=(
        resizable_buffer && rhs) noexcept
    {
        _allocator = std::move(rhs._allocator);
        _data = std::move(rhs._data);

        rhs._data = nullptr;
        return *this;
    }

    template <typename T, typename TAllocator>
    resizable_buffer<T, TAllocator>::~resizable_buffer() noexcept
    {
#if VRM_CORE_DEBUG
        VRM_CORE_ASSERT_OP(_data, ==, nullptr);
#endif
    }

    template <typename T, typename TAllocator>
    inline void resizable_buffer<T, TAllocator>::grow(
        size_type old_capacity, size_type new_capacity)
    {
        VRM_CORE_ASSERT_OP(old_capacity, <=, new_capacity);

        auto new_data(allocator_traits::allocate(_allocator, new_capacity));

        // Move existing items to new data.
        for(auto i(0u); i < old_capacity; ++i)
        {
            static_if(std::is_move_constructible<T>{})
                .then([&](auto& old_data)
                    {
                        new(&new_data[i]) T(std::move(old_data[i]));
                    })
                .else_([&](auto& old_data)
                    {
                        new(&new_data[i]) T(old_data[i]);
                    })(_data);
        }

        destroy_and_deallocate(old_capacity);
        _data = new_data;
    }

    template <typename T, typename TAllocator>
    inline void resizable_buffer<T, TAllocator>::construct(
        size_type from, size_type to)
    {
        for(auto i(from); i < to; ++i)
        {
            construct_at(i);
        }
    }

    template <typename T, typename TAllocator>
    inline void resizable_buffer<T, TAllocator>::grow_and_construct(
        size_type old_capacity, size_type new_capacity)
    {
        grow(old_capacity, new_capacity);
        construct(old_capacity, new_capacity);
    }

    template <typename T, typename TAllocator>
    inline auto resizable_buffer<T, TAllocator>::copy(size_type n)
    {
        this_type result{_allocator};
        result.grow(0, n);

        for(size_type i(0); i < n; ++i)
        {
            new(&result[i]) T((*this)[i]);
        }

        return result;
    }

    template <typename T, typename TAllocator>
    VRM_CORE_ALWAYS_INLINE auto resizable_buffer<T, TAllocator>::data() noexcept
    {
        return _data;
    }

    template <typename T, typename TAllocator>
    VRM_CORE_ALWAYS_INLINE auto resizable_buffer<T, TAllocator>::data()
        const noexcept
    {
        return _data;
    }

    template <typename T, typename TAllocator>
    VRM_CORE_ALWAYS_INLINE auto& resizable_buffer<T, TAllocator>::operator[](
        size_type idx) noexcept
    {
        VRM_CORE_ASSERT(_data != nullptr);
        return _data[idx];
    }

    template <typename T, typename TAllocator>
    VRM_CORE_ALWAYS_INLINE const auto& resizable_buffer<T, TAllocator>::
    operator[](size_type idx) const noexcept
    {
        VRM_CORE_ASSERT(_data != nullptr);
        return _data[idx];
    }
}
VRM_CORE_NAMESPACE_END
