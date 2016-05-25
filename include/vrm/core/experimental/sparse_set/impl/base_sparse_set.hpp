// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <type_traits>
#include <vrm/core/experimental/resizable_buffer.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases.hpp>
#include <vrm/core/casts.hpp>
#include <vrm/core/experimental/sparse_set/impl/storage.hpp>
#include <vrm/core/experimental/sparse_set/impl/settings.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        /// @brief Base implementation sparse set interface class.
        template <typename TSettings>
        class base_sparse_set
        {
        public:
            using settings_type = TSettings;
            using this_type = base_sparse_set<settings_type>;
            using size_type = typename settings_type::size_type;
            using value_type = typename settings_type::value_type;
            using storage_type = typename settings_type::storage_type;

            // TODO: support strong typedefs
            // The stored value has to be an unsigned arithmetic type.
            // VRM_CORE_STATIC_ASSERT_NM(std::is_unsigned<value_type>{});

        private:
            storage_type _impl;

        public:
            base_sparse_set() = default;

            base_sparse_set(const base_sparse_set& rhs) = default;
            base_sparse_set& operator=(const base_sparse_set& rhs) = default;

            base_sparse_set(base_sparse_set&&) = default;
            base_sparse_set& operator=(base_sparse_set&&) = default;

            /// @brief Returns `true` if `x` is in the set.
            bool has(value_type x) const noexcept;

            /// @brief Adds `x` in the set, returning `true` if it wasn't
            /// already present.
            bool add(value_type x) noexcept;

            /// @brief Removes `x` from the set, returning `true` if it was
            /// present.
            bool erase(value_type x) noexcept;

            /// @brief Adds `x` in the set, returning `true` if it wasn't
            /// already present. Assumes `!has(x)`.
            void unchecked_add(value_type x) noexcept;

            /// @brief Removes `x` from the set, returning `true` if it was
            /// present. Assumes `has(x)`.
            void unchecked_erase(value_type x) noexcept;

            /// @brief Clears the set.
            void clear() noexcept;

            /// @brief Returns `true` if the set is empty.
            bool empty() const noexcept;

            /// @brief Removes the last element of the set.
            /// @details Assumes the set is not empty.
            void pop_back() noexcept;

            /// @brief Returns the last element of the set.
            /// @details Assumes the set is not empty.
            auto back() const noexcept;

            /// @brief Executes `f` on every element of the set.
            template <typename TF>
            void for_each(TF&& f) const noexcept;

            /// @brief Returns the number of elements present in the set.
            auto size() const noexcept;

            /// @brief Returns the number of elements that can be stored in the
            /// set.
            auto capacity() const noexcept;

            // Iterator support.
            auto begin() noexcept;
            auto begin() const noexcept;
            auto end() noexcept;
            auto end() const noexcept;

            /// @brief Returns the `nth` value in the dense collection.
            /// @details Assumes `i` is a valid index.
            auto at(sz_t i) const noexcept;

            /// @brief Reserves memory for `n` elements if the underlying
            /// storage type supports it.
            /// @details If the underlying storage type is fixed or does not
            /// support reserving, this is a no-op.
            void reserve(sz_t n);

            /// @brief Swap implementation.
            void swap(this_type& rhs) noexcept;
        };
    }
}
VRM_CORE_NAMESPACE_END
