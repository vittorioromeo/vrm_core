// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <memory>
#include <tuple>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/experimental/resizable_buffer/resizable_buffer.hpp>
#include <vrm/core/tuple_utils.hpp>

VRM_CORE_NAMESPACE
{
    template <typename... TBufferTypes>
    class multi_resizable_buffer;

    template <typename... Ts>
    void swap(multi_resizable_buffer<Ts...> & lhs,
        multi_resizable_buffer<Ts...> & rhs) // .
        noexcept(noexcept(lhs.swap(rhs)));

    template <typename... TBufferTypes>
    class VRM_CORE_CLASS_API multi_resizable_buffer
    {
        VRM_CORE_STATIC_ASSERT_NM(sizeof...(TBufferTypes) > 0);

    private:
        using this_type = multi_resizable_buffer<TBufferTypes...>;

        template <typename TBuffer>
        using buffer_data_ptr_type = typename TBuffer::data_ptr_type;

        template <typename TBuffer>
        using buffer_value_type = typename TBuffer::value_type;

        using buffer_indices =
            std::make_index_sequence<sizeof...(TBufferTypes)>;

        using buffer_tuple = std::tuple<TBufferTypes...>;

    public:
        using size_type = sz_t;

        using data_ptr_tuple =
            std::tuple<buffer_data_ptr_type<TBufferTypes>...>;

        using value_tuple = std::tuple<buffer_value_type<TBufferTypes>...>;

        using value_reference_tuple =
            std::tuple<buffer_value_type<TBufferTypes>&...>;

        using const_value_reference_tuple =
            std::tuple<const buffer_value_type<TBufferTypes>&...>;

        template <sz_t TN>
        using nth_buffer_type = std::tuple_element_t<TN, buffer_tuple>;

        template <sz_t TN>
        using nth_buffer_value_type = buffer_value_type<nth_buffer_type<TN>>;

        static constexpr sz_t buffer_count{sizeof...(TBufferTypes)};

    private:
        buffer_tuple _buffers;

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


    public:
        template <sz_t TN>
        VRM_CORE_ALWAYS_INLINE auto& nth_buffer()
        {
            VRM_CORE_STATIC_ASSERT_NM(buffer_count > TN);
            return std::get<TN>(_buffers);
        }

        template <typename T>
        VRM_CORE_ALWAYS_INLINE auto& buffer_of()
        {
            // TODO:
            // return std::get<>(_buffers);
        }



        multi_resizable_buffer() = default;

        multi_resizable_buffer(const multi_resizable_buffer&) = delete;
        multi_resizable_buffer& operator=(
            const multi_resizable_buffer&) = delete;

        multi_resizable_buffer(multi_resizable_buffer&& rhs) = default;
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
                    auto& my_buffer(this->nth_buffer<decltype(data)::index>());
                    auto& result_buffer(
                        result.nth_buffer<decltype(data)::index>());

                    result_buffer = std::move(my_buffer.copy(n));
                },
                _buffers);

            return result;
        }

        void swap(multi_resizable_buffer& rhs) noexcept
        {
            using std::swap;
            swap(_buffers, rhs._buffers);
        }

    private:
        template <sz_t... TIs>
        auto data_builder(std::index_sequence<TIs...>) noexcept
        {
            return data_ptr_tuple{std::get<TIs>(_buffers).data()...};
        }

        template <sz_t... TIs>
        auto data_builder(std::index_sequence<TIs...>) const noexcept
        {
            return data_ptr_tuple{std::get<TIs>(_buffers).data()...};
        }

    public:
        auto data() noexcept { return data_builder(buffer_indices{}); }

        auto data() const noexcept { return data_builder(buffer_indices{}); }

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

    template <typename... Ts>
    VRM_CORE_ALWAYS_INLINE void swap(multi_resizable_buffer<Ts...> & lhs,
        multi_resizable_buffer<Ts...> & rhs) // .
        noexcept(noexcept(lhs.swap(rhs)))
    {
        lhs.swap(rhs);
    }
}
VRM_CORE_NAMESPACE_END

// TODO:
// * split to inl
// * noexcept
// * review
