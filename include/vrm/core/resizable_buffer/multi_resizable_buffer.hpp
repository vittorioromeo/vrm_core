// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <memory>
#include <tuple>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/resizable_buffer/resizable_buffer.hpp>
#include <vrm/core/tuple_utils.hpp>

VRM_CORE_NAMESPACE
{
    template <typename... TBufferTypes>
    class VRM_CORE_CLASS_API multi_resizable_buffer
    {
        VRM_CORE_STATIC_ASSERT_NM(sizeof...(TBufferTypes) > 0);

    private:
        using this_type = multi_resizable_buffer<TBufferTypes...>;

    public:
        using size_type = std::size_t;

        using data_ptr_tuple =
            std::tuple<typename TBufferTypes::data_ptr_type...>;

        using value_reference_tuple =
            std::tuple<typename TBufferTypes::value_type&...>;

        using const_value_reference_tuple =
            std::tuple<const typename TBufferTypes::value_type&...>;

    private:
        std::tuple<TBufferTypes...> _buffers;

        template <typename TF>
        VRM_CORE_ALWAYS_INLINE void for_buffers(TF&& f)
        {
            for_tuple(
                [&f](auto& bx)
                {
                    f(bx);
                },
                _buffers);
        }

        template <std::size_t TN>
        VRM_CORE_ALWAYS_INLINE auto& nth_buffer()
        {
            return std::get<TN>(_buffers);
        }

    public:
        multi_resizable_buffer() = default;


        multi_resizable_buffer(const multi_resizable_buffer&) = delete;
        multi_resizable_buffer& operator=(
            const multi_resizable_buffer&) = delete;

        multi_resizable_buffer(multi_resizable_buffer&& rhs) = default;
        /*{
            for_tuple_data(
                [this, &rhs](auto data, auto&)
                {
                    using my_buffer_type =
                        std::tuple_element_t<decltype(data)::index,
                            decltype(_buffers)>;

                    auto& my_buffer(nth_buffer<decltype(data)::index>());
                    auto& rhs_buffer(rhs.nth_buffer<decltype(data)::index>());

                    new(&my_buffer) my_buffer_type(std::move(rhs_buffer));
                },
                _buffers);
        }*/

        multi_resizable_buffer& operator=(multi_resizable_buffer&&) = default;

        void construct_at(size_type idx)
        {
            for_buffers([this, &idx](auto& b)
                {
                    b.construct_at(idx);
                });
        }

        void destroy_at(size_type idx)
        {
            for_buffers([this, &idx](auto& b)
                {
                    b.destroy_at(idx);
                });
        }

        void destroy(size_type from, size_type to)
        {
            for_buffers([this, &from, &to](auto& b)
                {
                    b.destroy(from, to);
                });
        }

        void deallocate(size_type n)
        {
            for_buffers([this, &n](auto& b)
                {
                    b.deallocate(n);
                });
        }

        void destroy_and_deallocate(size_type n)
        {
            for_buffers([this, &n](auto& b)
                {
                    b.destroy_and_deallocate(n);
                });
        }


        void grow(size_type old_capacity, size_type new_capacity)
        {
            for_buffers([this, &old_capacity, &new_capacity](auto& b)
                {
                    b.grow(old_capacity, new_capacity);
                });
        }

        void construct(size_type from, size_type to)
        {
            for_buffers([this, &from, &to](auto& b)
                {
                    b.construct(from, to);
                });
        }


        void grow_and_construct(size_type old_capacity, size_type new_capacity)
        {
            for_buffers([this, &old_capacity, &new_capacity](auto& b)
                {
                    b.grow_and_construct(old_capacity, new_capacity);
                });
        }

        auto copy(size_type n)
        {
            this_type result;

            for_tuple_data(
                [this, &result, &n](auto data, auto&)
                {
                    auto& my_buffer(nth_buffer<decltype(data)::index>());
                    auto& result_buffer(
                        result.nth_buffer<decltype(data)::index>());

                    result_buffer = std::move(my_buffer.copy(n));
                },
                _buffers);

            return result;
        }

        auto data() noexcept
        {
            return data_ptr_tuple{std::get<TBufferTypes>(_buffers).data()...};
        }

        auto data() const noexcept
        {
            return data_ptr_tuple{std::get<TBufferTypes>(_buffers).data()...};
        }

        auto operator[](size_type pos) noexcept
        {
            return value_reference_tuple{
                std::get<TBufferTypes>(_buffers)[pos]...};
        }

        auto operator[](size_type pos) const noexcept
        {
            return const_value_reference_tuple{
                std::get<TBufferTypes>(_buffers)[pos]...};
        }
    };
}
VRM_CORE_NAMESPACE_END
