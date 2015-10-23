// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <memory>
#include <vrm/core/internal.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/resizable_buffer/resizable_buffer.hpp>
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
    void resizable_buffer<T, TAllocator>::destroy(size_type n)
    {
#if VRM_CORE_DEBUG
        if(n > 0)
        {
            VRM_CORE_ASSERT_OP(_data, !=, nullptr);
        }
#endif

        for(auto i(0u); i < n; ++i)
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
        destroy(n);
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
    auto& resizable_buffer<T, TAllocator>::operator=(
        resizable_buffer && rhs) noexcept
    {
        _allocator = std::move(rhs._allocator);
        _data = std::move(rhs._data);

        rhs._data = nullptr;
        return *this;
    }

#if VRM_CORE_DEBUG
    template <typename T, typename TAllocator>
    resizable_buffer<T, TAllocator>::~resizable_buffer() noexcept
    {
        VRM_CORE_ASSERT_OP(_data, ==, nullptr);
    }
#endif

    template <typename T, typename TAllocator>
    inline void resizable_buffer<T, TAllocator>::grow(
        size_type old_capacity, size_type new_capacity)
    {
        VRM_CORE_ASSERT_OP(old_capacity, <=, new_capacity);

        auto new_data(allocator_traits::allocate(_allocator, new_capacity));

        // Move existing items to new data.
        for(auto i(0u); i < old_capacity; ++i)
        {
            new_data[i] = std::move(_data[i]);
        }

        destroy_and_deallocate(old_capacity);
        _data = new_data;
    }

    template <typename T, typename TAllocator>
    inline void resizable_buffer<T, TAllocator>::grow_and_construct(
        size_type old_capacity, size_type new_capacity)
    {
        grow(old_capacity, new_capacity);

        // Default-construct new items.
        for(auto i(old_capacity); i < new_capacity; ++i)
        {
            construct_at(i);
        }
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