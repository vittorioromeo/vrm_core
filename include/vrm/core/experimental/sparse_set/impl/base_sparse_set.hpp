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
            using size_type = typename TSettings::size_type;
            using value_type = typename TSettings::value_type;
            using storage_type = typename TSettings::storage_type;

            // The stored value has to be an unsigned arithmetic type.
            VRM_CORE_STATIC_ASSERT_NM(std::is_unsigned<value_type>{});

        private:
            storage_type _impl;

        public:
            base_sparse_set() = default;

            base_sparse_set(const base_sparse_set& rhs) = default;
            base_sparse_set& operator=(const base_sparse_set& rhs) = default;

            base_sparse_set(base_sparse_set&&) = default;
            base_sparse_set& operator=(base_sparse_set&&) = default;

            bool has(value_type x) const noexcept;
            bool add(value_type x) noexcept;
            bool erase(value_type x) noexcept;

            void clear() noexcept;
            bool empty() const noexcept;

            void pop_back() noexcept;
            auto back() const noexcept;

            template <typename TF>
            void for_each(TF&& f) const noexcept;

            auto size() const noexcept;

            auto begin() noexcept;
            auto begin() const noexcept;

            auto end() noexcept;
            auto end() const noexcept;

            auto& operator[](sz_t i) noexcept;
            const auto& operator[](sz_t i) const noexcept;
        };
    }
}
VRM_CORE_NAMESPACE_END
