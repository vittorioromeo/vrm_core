// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <vrm/core/experimental/resizable_buffer.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases.hpp>
#include <vrm/core/casts.hpp>
#include <vrm/core/experimental/sparse_set/impl/storage.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T, typename TStorage>
        struct sparse_set_settings
        {
            VRM_CORE_STATIC_ASSERT_NM(
                std::is_arithmetic<T>{} && std::is_unsigned<T>{});

            using size_type = sz_t;
            using value_type = T;
            using storage_type = TStorage;
        };

        template <typename TSettings>
        class base_sparse_set
        {

        public:
            using size_type = typename TSettings::size_type;
            using value_type = typename TSettings::value_type;
            using storage_type = typename TSettings::storage_type;

        private:
            storage_type _impl;

        public:
            base_sparse_set() = default;

            base_sparse_set(const base_sparse_set& rhs) = default;
            base_sparse_set& operator=(const base_sparse_set& rhs) = default;

            base_sparse_set(base_sparse_set&&) = default;
            base_sparse_set& operator=(base_sparse_set&&) = default;

            bool has(const value_type& x) const noexcept;
            bool add(const value_type& x) noexcept;
            bool erase(const value_type& x) noexcept;

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
        };
    }
}
VRM_CORE_NAMESPACE_END
