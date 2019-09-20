// Copyright (c) 2015-2019 Vittorio Romeo
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
    // Assumes that the memory location of the buffers will never
    // change.

    template <                    // .
        typename T,               // .
        sz_t TCapacity,           // .
        typename TDenseAllocator, // .
        typename TSparseAllocator // .
        >
    class fixed_vector
    {
        friend class sparse_set_storage::utils;

    public:
        using value_type = T;
        using sparse_type = T*;
        using dense_allocator_type = TDenseAllocator;
        using sparse_allocator_type = TSparseAllocator;

    private:
        multi_resizable_buffer<                                  // .
            resizable_buffer<value_type, dense_allocator_type>,  // .
            resizable_buffer<sparse_type, sparse_allocator_type> // .
            >
            _buffers;

        sparse_type _end;

        VRM_CORE_ALWAYS_INLINE auto &dense() noexcept
        {
            return _buffers.template nth_buffer<0>();
        }

        VRM_CORE_ALWAYS_INLINE auto &sparse() noexcept
        {
            return _buffers.template nth_buffer<1>();
        }

        [[nodiscard]] VRM_CORE_ALWAYS_INLINE const auto &dense() const noexcept
        {
            return _buffers.template nth_buffer<0>();
        }

        [[nodiscard]] VRM_CORE_ALWAYS_INLINE const auto &sparse() const noexcept
        {
            return _buffers.template nth_buffer<1>();
        }

        [[nodiscard]] VRM_CORE_ALWAYS_INLINE auto last_element_ptr() const
            noexcept
        {
            return _end - 1;
        }

        void reinitialize_from_move(fixed_vector &rhs) noexcept
        {
            // Store `rhs`' size, to later recalculate `_end`.
            auto temp_size = rhs.size();

            // Move the buffers.
            // `rhs`'s buffers will be set to null.
            _buffers = std::move(rhs._buffers);

            // Recalculate end pointer.
            _end = dense().data() + temp_size;
        }

        void grow_if_required(T) noexcept
        {
            // Intentionally empty.
        }

        void set_last_element(T x) noexcept
        {
            *_end = x;
            sparse()[x] = _end;
            ++_end;
        }

        bool is_null(sparse_type x) noexcept
        {
            return x == nullptr;
        }

        void nullify(T x) noexcept
        {
            sparse()[x] = nullptr;
        }

        void decrement_size() noexcept
        {
            --_end;
        }

        auto &value_from_sparse(sparse_type x) noexcept
        {
            return *x;
        }

    public:
        fixed_vector()
        {
            // Only growth call in the storage.
            _buffers.grow(0, TCapacity);

            // Initialize sprase array to `nullptr`.
            for(decltype(TCapacity) i(0); i < TCapacity; ++i)
            {
                sparse()[i] = nullptr;
            }

            // Initialize end pointer.
            _end = dense().data();
        }

        ~fixed_vector()
        {
            if(!_buffers.null())
            {
                _buffers.destroy_and_deallocate(TCapacity);
            }
        }

        // Prevent copies.
        fixed_vector(const fixed_vector &) = delete;
        fixed_vector &operator=(const fixed_vector &) = delete;

        // TODO: test
        fixed_vector(fixed_vector &&rhs) noexcept
        {
            reinitialize_from_move(rhs);
        }

        fixed_vector &operator=(fixed_vector &&rhs) noexcept
        {
            reinitialize_from_move(rhs);
            return *this;
        }

        void reserve(sz_t) noexcept
        {
            // Intentionally empty.
        }

        void clear() noexcept
        {
            // Clear all used set elements.
            for_each([this](auto x) { sparse()[x] = nullptr; });

            // Re-initalize end pointer.
            _end = dense().data();
        }

        [[nodiscard]] bool has(T x) const noexcept
        {
            VRM_CORE_ASSERT_OP(x, <, TCapacity);
            return sparse()[x] != nullptr;
        }

        [[nodiscard]] auto capacity() const noexcept
        {
            return TCapacity;
        }

        bool add(T x) noexcept
        {
            VRM_CORE_ASSERT_OP(x, <, TCapacity);
            return utils{}.add_impl(*this, x);
        }

        bool erase(T x) noexcept
        {
            VRM_CORE_ASSERT_OP(x, <, TCapacity);
            return utils{}.erase_impl(*this, x);
        }

        void unchecked_add(T x) noexcept
        {
            VRM_CORE_ASSERT_OP(x, <, TCapacity);
            return utils{}.unchecked_add(*this, x);
        }

        void unchecked_erase(T x) noexcept
        {
            VRM_CORE_ASSERT_OP(x, <, TCapacity);
            return utils{}.unchecked_erase(*this, x);
        }


        [[nodiscard]] bool empty() const noexcept
        {
            return _end == dense().data();
        }

        void pop_back() noexcept
        {
            utils{}.pop_back_impl(*this);
        }

        [[nodiscard]] auto back() const noexcept
        {
            VRM_CORE_ASSERT_OP(size(), >, 0);

            VRM_CORE_ASSERT(has(*(last_element_ptr())));
            return *(last_element_ptr());
        }

        template <typename TF>
        void for_each(TF &&f) const noexcept
        {
            VRM_CORE_ASSERT_OP(size(), <=, TCapacity);

            for(auto p(dense().data()); p != _end; ++p)
            {
                VRM_CORE_ASSERT(has(*p));
                f(*p);
            }
        }

        [[nodiscard]] auto size() const noexcept
        {
            return to_sz_t(end() - begin());
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
            return _end;
        }

        [[nodiscard]] auto end() const noexcept
        {
            return static_cast<const T*>(_end);
        }

        [[nodiscard]] auto at(sz_t i) const noexcept
        {
            VRM_CORE_ASSERT_OP(i, <, size());
            return dense()[i];
        }

        void swap(fixed_vector &rhs) noexcept
        {
            using std::swap;
            swap(_buffers, rhs._buffers);
            swap(_end, rhs._end);
        }
    };
} // namespace vrm::core::impl::sparse_set_storage
