// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/weak/weak.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            template <typename TBehavior, typename TLockPolicy>
            weak<TBehavior, TLockPolicy>::weak() noexcept
            {
            }

            template <typename TBehavior, typename TLockPolicy>
            weak<TBehavior, TLockPolicy>::weak(const weak& rhs) noexcept
                : _handle{rhs._handle},
                  _ref_counter{rhs._ref_counter}
            {
                _ref_counter.increment_weak();
            }

            template <typename TBehavior, typename TLockPolicy>
            weak<TBehavior, TLockPolicy>::weak(const shared_type& rhs) noexcept
                : _handle{rhs._handle},
                  _ref_counter{rhs._ref_counter}
            {
                _ref_counter.increment_weak();
            }

            template <typename TBehavior, typename TLockPolicy>
            weak<TBehavior, TLockPolicy>::weak(weak&& rhs) noexcept
            {
                // TODO:
            }

            template <typename TBehavior, typename TLockPolicy>
            auto& weak<TBehavior, TLockPolicy>::operator=(
                const weak& rhs) noexcept
            {
                assert(this != &rhs);

                _handle = rhs._handle;
                _ref_counter = rhs._ref_counter;
                _ref_counter.increment_weak();

                return *this;
            }

            template <typename TBehavior, typename TLockPolicy>
            auto& weak<TBehavior, TLockPolicy>::operator=(
                const shared_type& rhs) noexcept
            {
                _handle = rhs._handle;
                _ref_counter = rhs._ref_counter;
                _ref_counter.increment_weak();

                return *this;
            }

            template <typename TBehavior, typename TLockPolicy>
            auto& weak<TBehavior, TLockPolicy>::operator=(weak&& rhs) noexcept
            {
                // TODO:
                return *this;
            }

            template <typename TBehavior, typename TLockPolicy>
            weak<TBehavior, TLockPolicy>::~weak()
            {
                reset();
            }

            template <typename TBehavior, typename TLockPolicy>
            void weak<TBehavior, TLockPolicy>::swap(weak& rhs) noexcept
            {
                using std::swap;
                swap(_handle, rhs._handle);
                swap(_ref_counter, rhs._ref_counter);
            }

            template <typename TBehavior, typename TLockPolicy>
            void weak<TBehavior, TLockPolicy>::reset() noexcept
            {
                _ref_counter.lose_weak([this]
                    {
                        behavior_type::deinit(_handle);
                    });

                _handle = behavior_type::null_handle();
                _ref_counter = ref_counter_type{};
            }

            template <typename TBehavior, typename TLockPolicy>
            auto weak<TBehavior, TLockPolicy>::use_count() const noexcept
            {
                return _ref_counter.use_count();
            }

            template <typename TBehavior, typename TLockPolicy>
            auto weak<TBehavior, TLockPolicy>::expired() const noexcept
            {
                if(_ref_counter.is_null())
                {
                    return true;
                }

                return _ref_counter.owner_count() == 0;
            }

            template <typename TBehavior, typename TLockPolicy>
            auto weak<TBehavior, TLockPolicy>::lock() const noexcept
            {
                if(expired())
                {
                    return shared_type{};
                }

                return shared_type{*this};
            }
        }

        // TODO: swap, comparison ops
        // TODO: docs
    }
}
VRM_CORE_NAMESPACE_END
