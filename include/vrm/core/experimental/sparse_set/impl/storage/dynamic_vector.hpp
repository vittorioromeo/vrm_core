// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include "./shared.hpp"
#include <vrm/core/assert.hpp>
#include <vrm/core/casts.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resizable_buffer.hpp>
#include <vrm/core/type_aliases.hpp>

namespace vrm::core::impl::sparse_set_storage
{
    template <                    // .
        typename T,               // .
        typename TDenseAllocator, // .
        typename TSparseAllocator // .
        >
    class dynamic_vector
    {
        friend class sparse_set_storage::utils;

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
            >
            _buffers;

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

        void grow_to(sz_t new_capacity)
        {
            VRM_CORE_ASSERT_OP(new_capacity, >=, _capacity);
            grow_by(new_capacity - _capacity);
        }

        [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto& dense() noexcept
        {
            return _buffers.template nth_buffer<0>();
        }

        [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto& sparse() noexcept
        {
            return _buffers.template nth_buffer<1>();
        }

        [[nodiscard]] VRM_CORE_ALWAYS_INLINE const auto& dense() const noexcept
        {
            return _buffers.template nth_buffer<0>();
        }

        [[nodiscard]] VRM_CORE_ALWAYS_INLINE const auto& sparse() const noexcept
        {
            return _buffers.template nth_buffer<1>();
        }

        [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto
        last_element_index() const noexcept
        {
            return _size - 1;
        }

        void grow_if_required(T x)
        {
            // Since we need to access `sparse[x]`, growing only for
            // size is not sufficient. We also have to check `x`.
            VRM_CORE_ASSERT_OP(size(), <=, _capacity);
            if(likely(x < _capacity))
            {
                return;
            }

            // TODO: review growth policy
            auto target(std::max(to_sz_t(x), to_sz_t(_capacity)));
            grow_by(target + 32);

            VRM_CORE_ASSERT_OP(_capacity, >, x);
        }

        void set_last_element(T x) noexcept
        {
            dense()[_size] = x;
            sparse()[x] = _size;
            ++_size;
        }

        [[nodiscard]] bool is_null(sparse_type x) noexcept
        {
            return x == null_idx;
        }

        void nullify(T x) noexcept
        {
            sparse()[x] = null_idx;
        }

        void decrement_size() noexcept
        {
            --_size;
        }

        [[nodiscard]] auto& value_from_sparse(sparse_type x) noexcept
        {
            return dense()[x];
        }

    public:
        dynamic_vector()
        {
            grow_by(64);
            _size = 0;
        }

        ~dynamic_vector()
        {
            if(!_buffers.null())
            {
                _buffers.destroy_and_deallocate(_capacity);
            }
        }

        dynamic_vector(const dynamic_vector& rhs)
            : _buffers{rhs._buffers.copy(rhs._size)}, _size{rhs._size},
              _capacity{rhs._capacity}
        {
        }

        dynamic_vector& operator=(const dynamic_vector& rhs)
        {
            _buffers = rhs._buffers.copy(rhs._size);
            _size = rhs._size;
            _capacity = rhs._capacity;

            return *this;
        }

        dynamic_vector(dynamic_vector&&) = default;
        dynamic_vector& operator=(dynamic_vector&&) = default;

        void reserve(sz_t n)
        {
            // Exit early if there is no need to reserve.
            if(unlikely(_capacity >= n))
            {
                return;
            }

            grow_to(n);
        }

        void clear() noexcept
        {
            for_each([this](auto x) { sparse()[x] = null_idx; });

            _size = 0;
        }

        [[nodiscard]] bool has(T x) const noexcept
        {
            // If `x` cannot be stored, then it's not in the set.
            if(x >= _capacity)
            {
                return false;
            }

            return sparse()[x] != null_idx;
        }

        [[nodiscard]] auto capacity() const noexcept
        {
            return _capacity;
        }

        bool add(T x)
        {
            return utils{}.add_impl(*this, x);
        }

        bool erase(T x) noexcept
        {
            return utils{}.erase_impl(*this, x);
        }

        void unchecked_add(T x)
        {
            return utils{}.unchecked_add(*this, x);
        }

        void unchecked_erase(T x) noexcept
        {
            return utils{}.unchecked_erase(*this, x);
        }

        [[nodiscard]] bool empty() const noexcept
        {
            return _size == 0;
        }

        void pop_back() noexcept
        {
            utils{}.pop_back_impl(*this);
        }

        [[nodiscard]] auto back() const noexcept
        {
            VRM_CORE_ASSERT_OP(size(), >, 0);

            VRM_CORE_ASSERT(has(dense()[last_element_index()]));
            return dense()[last_element_index()];
        }

        template <typename TF>
        void for_each(TF&& f) const noexcept
        {
            VRM_CORE_ASSERT_OP(size(), <=, _capacity);

            for(decltype(_size) i(0); i < _size; ++i)
            {
                VRM_CORE_ASSERT(has(dense()[i]));
                f(dense()[i]);
            }
        }

        [[nodiscard]] auto size() const noexcept
        {
            return _size;
        }

        auto begin() noexcept
        {
            return dense().data();
        }

        [[nodiscard]] auto begin() const noexcept
        {
            return static_cast<const T*>(dense().data());
        }

        auto end() noexcept
        {
            return dense().data() + _size;
        }

        [[nodiscard]] auto end() const noexcept
        {
            return static_cast<const T*>(dense().data() + _size);
        }

        [[nodiscard]] auto at(sz_t i) const noexcept
        {
            VRM_CORE_ASSERT_OP(i, <, size());
            return dense()[i];
        }

        void swap(dynamic_vector& rhs) noexcept
        {
            using std::swap;
            swap(_buffers, rhs._buffers);
            swap(_size, rhs._size);
            swap(_capacity, rhs._capacity);
        }
    };
} // namespace vrm::core::impl::sparse_set_storage
