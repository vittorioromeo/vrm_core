// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/experimental/sparse_set/impl/base_sparse_set.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TSettings>
        bool base_sparse_set<TSettings>::has(const value_type& x) const noexcept
        {
            return _impl.has(x);
        }

        template <typename TSettings>
        bool base_sparse_set<TSettings>::add(const value_type& x) noexcept
        {
            return _impl.add(x);
        }

        template <typename TSettings>
        bool base_sparse_set<TSettings>::erase(const value_type& x) noexcept
        {
            return _impl.erase(x);
        }

        template <typename TSettings>
        void base_sparse_set<TSettings>::clear() noexcept
        {
            _impl.clear();
        }

        template <typename TSettings>
        bool base_sparse_set<TSettings>::empty() const noexcept
        {
            return _impl.empty();
        }

        template <typename TSettings>
        void base_sparse_set<TSettings>::pop_back() noexcept
        {
            _impl.pop_back();
        }

        template <typename TSettings>
        auto base_sparse_set<TSettings>::back() const noexcept
        {
            return _impl.back();
        }

        template <typename TSettings>
        template <typename TF>
        void base_sparse_set<TSettings>::for_each(TF&& f) const noexcept
        {
            _impl.for_each(FWD(f));
        }

        template <typename TSettings>
        auto base_sparse_set<TSettings>::size() const noexcept
        {
            return _impl.size();
        }

        template <typename TSettings>
        auto base_sparse_set<TSettings>::begin() noexcept
        {
            return _impl.begin();
        }

        template <typename TSettings>
        auto base_sparse_set<TSettings>::begin() const noexcept
        {
            return _impl.begin();
        }

        template <typename TSettings>
        auto base_sparse_set<TSettings>::end() noexcept
        {
            return _impl.end();
        }

        template <typename TSettings>
        auto base_sparse_set<TSettings>::end() const noexcept
        {
            return _impl.end();
        }
    }
}
VRM_CORE_NAMESPACE_END
