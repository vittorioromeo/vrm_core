// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/assert.hpp>
#include <vrm/core/delegate/base_delegate.hpp>

// TODO: WIP:
// * use sparse int set?

VRM_CORE_NAMESPACE 
{
    
}
VRM_CORE_NAMESPACE_END

VRM_CORE_NAMESPACE
{


    template <typename>
    class dynamic_delegate;

    template <typename>
    class dynamic_delegate_handle;

    template <typename TReturn, typename... TArgs>
    class dynamic_delegate_handle<TReturn(TArgs...)>
    {
        template <typename>
        friend class dynamic_delegate;

    private:
        std::size_t _index;
        int8_t _counter;

        dynamic_delegate_handle(std::size_t index, int8_t counter) noexcept
            : _index{index},
              _counter{counter}
        {
        }
    };

    template <typename TReturn, typename... TArgs>
    class dynamic_delegate<TReturn(TArgs...)>
        : public impl::base_delegate<TReturn(TArgs...)>
    {
    public:
        using handle_type = dynamic_delegate_handle<TReturn(TArgs...)>;

    private:
        struct handle_data
        {
            std::size_t _target_idx;
            int8_t _counter;

            handle_data(std::size_t target_idx, int8_t counter) noexcept
                : _target_idx{target_idx},
                  _counter{counter}
            {
            }
        };

        using base_type = impl::base_delegate<TReturn(TArgs...)>;
        std::vector<handle_data> _handle_data;

        auto& handle_data_from_handle(const handle_type& h) noexcept
        {
            VRM_CORE_ASSERT_OP(_handle_data.size(), >, h._index);
            return _handle_data[h._index];
        }

        const auto& handle_data_from_handle(const handle_type& h) const noexcept
        {
            VRM_CORE_ASSERT_OP(_handle_data.size(), >, h._index);
            return _handle_data[h._index];
        }

        auto valid_handle(const handle_type& h) noexcept
        {
            return h._counter == handle_data_from_handle(h)._counter;
        }

        void erase_at(std::size_t idx)
        {
            VRM_CORE_ASSERT_OP(this->_functions.size(), >, idx);
            this->_functions.erase(std::begin(this->_functions) + idx);

            for(auto i(idx); i < _handle_data.size(); ++i)
            {
                _handle_data[i]._target_idx -= 1;
            }
        }

    public:
        using fn_type = typename base_type::fn_type;

    public:
        template <typename TF>
        auto operator+=(TF&& f)
        {
            auto idx(this->_functions.size());
            this->emplace_function(FWD(f));

            if(_handle_data.size() <= idx)
            {
                _handle_data.emplace_back(idx, 0);
            }
            else
            {
                _handle_data[idx]._target_idx = idx;
            }

            handle_type h{idx, _handle_data[idx]._counter};
            VRM_CORE_ASSERT(valid_handle(h));

            return h;
        }

        void operator-=(const handle_type& h)
        {
            VRM_CORE_ASSERT(valid_handle(h));
            ++(handle_data_from_handle(h)._counter);
            erase_at(h._index);
            VRM_CORE_ASSERT(!valid_handle(h));
        }
    };
}
VRM_CORE_NAMESPACE_END