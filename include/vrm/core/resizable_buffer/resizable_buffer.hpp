// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <memory>
#include <vrm/core/internal.hpp>
#include <vrm/core/assert.hpp>

namespace std
{
    auto& operator<<(std::ostream& o, const std::nullptr_t&)
    {
        o << "nullptr";
        return o;
    }
}

VRM_CORE_NAMESPACE
{
    template <typename T, typename TAllocator = ::std::allocator<T>>
    class resizable_buffer
    {
    private:
        using this_type = resizable_buffer<T, TAllocator>;

    public:
        using value_type = T;
        using allocator_type = TAllocator;
        using allocator_traits = ::std::allocator_traits<allocator_type>;

    private:
        allocator_type _allocator;
        T* _data{nullptr};

        void destroy_and_deallocate(std::size_t capacity)
        {
            VRM_CORE_ASSERT_OP(_data, !=, nullptr);

            for(auto i(0u); i < capacity; ++i)
                allocator_traits::destroy(_allocator, _data + i);

            allocator_traits::deallocate(_allocator, _data, capacity);

#if VRM_CORE_DEBUG
            _data = nullptr;
#endif
        }

    public:
        resizable_buffer(const TAllocator& allocator = TAllocator{})
            : _allocator{allocator}
        {
        }

        resizable_buffer(resizable_buffer&& rhs) noexcept
            : _allocator{std::move(rhs._allocator)},
              _data{std::move(rhs._data)}
        {
            rhs._data = nullptr;
        }

        resizable_buffer& operator=(resizable_buffer&& rhs) noexcept
        {
            _allocator = std::move(rhs._allocator);
            _data = std::move(rhs._data);

            rhs._data = nullptr;
            return *this;
        }

        ~resizable_buffer() noexcept
        {
            VRM_CORE_ASSERT_OP(_data, ==, nullptr);
        }

        void cleanup(std::size_t capacity) { destroy_and_deallocate(capacity); }

        resizable_buffer(const resizable_buffer& rhs) = delete;
        resizable_buffer& operator=(const resizable_buffer& rhs) = delete;

        /// @brief Grows the internal storage from `old_capacity` to
        /// `new_capacity`.
        /// @details The new capacity must be greater or equal than the old one.
        inline void grow(std::size_t old_capacity, std::size_t new_capacity)
        {
            VRM_CORE_ASSERT_OP(old_capacity, <=, new_capacity);

            auto new_data(allocator_traits::allocate(_allocator, new_capacity));

            // Move existing items to new data.
            for(auto i(0u); i < old_capacity; ++i)
                new_data[i] = std::move(_data[i]);

            if(old_capacity != 0) destroy_and_deallocate(old_capacity);
            _data = new_data;

            // Default-construct new items.
            for(auto i(old_capacity); i < new_capacity; ++i)
                allocator_traits::construct(_allocator, _data + i);
        }

        VRM_CORE_ALWAYS_INLINE auto data() noexcept { return _data; }

        VRM_CORE_ALWAYS_INLINE auto data() const noexcept { return _data; }

        VRM_CORE_ALWAYS_INLINE auto& operator[](std::size_t idx) noexcept
        {
            VRM_CORE_ASSERT(_data != nullptr);
            return _data[idx];
        }

        VRM_CORE_ALWAYS_INLINE const auto& operator[](std::size_t idx) const
            noexcept
        {
            VRM_CORE_ASSERT(_data != nullptr);
            return _data[idx];
        }
    };
}
VRM_CORE_NAMESPACE_END