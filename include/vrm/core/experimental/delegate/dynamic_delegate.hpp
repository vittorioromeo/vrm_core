// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/delegate/base_delegate.hpp>
#include <vrm/core/type_aliases/numerical.hpp>

// TODO: WIP:
// * use sparse int set?

VRM_CORE_NAMESPACE {}
VRM_CORE_NAMESPACE_END

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        using index_type = sz_t;
        using counter_type = std::int8_t;

        struct handle_data
        {
            index_type _index;
            counter_type _counter;

            VRM_CORE_ALWAYS_INLINE handle_data(index_type index,
                counter_type counter) noexcept : _index{index},
                                                 _counter{counter}
            {
            }
        };

        template <template <typename...> class TFunction, typename TSignature>
        class VRM_CORE_CLASS_API dynamic_delegate_handle : public handle_data
        {
            template <template <typename...> class, typename>
            friend class dynamic_delegate;

        private:
            using handle_data::handle_data;

            const auto& target_idx() const noexcept { return _index; }
            const auto& counter() const noexcept { return _counter; }
        };


        template <template <typename...> class TFunction, typename TSignature>
        class VRM_CORE_CLASS_API dynamic_delegate
            : public impl::base_delegate<TFunction, TSignature>
        {
        public:
            using handle_type = dynamic_delegate_handle<TFunction, TSignature>;

        private:
            using base_type = impl::base_delegate<TFunction, TSignature>;
            std::vector<handle_data> _handle_data;

            auto& handle_data_from_handle(const handle_type& h) noexcept
            {
                VRM_CORE_ASSERT_OP(_handle_data.size(), >, h.target_idx());
                return _handle_data[h.target_idx()];
            }

            const auto& handle_data_from_handle(const handle_type& h) const
                noexcept
            {
                VRM_CORE_ASSERT_OP(_handle_data.size(), >, h.target_idx());
                return _handle_data[h.target_idx()];
            }

            auto valid_handle(const handle_type& h) noexcept
            {
                return h.counter() == handle_data_from_handle(h)._counter;
            }

            void erase_at(sz_t idx)
            {
                VRM_CORE_ASSERT_OP(this->_functions.size(), >, idx);
                this->_functions.erase(std::begin(this->_functions) + idx);

                for(auto i(idx); i < _handle_data.size(); ++i)
                {
                    _handle_data[i]._index -= 1;
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
                    _handle_data[idx]._index = idx;
                }

                handle_type h{idx, _handle_data[idx]._counter};
                VRM_CORE_ASSERT(valid_handle(h));

                return h;
            }

            void operator-=(const handle_type& h)
            {
                VRM_CORE_ASSERT(valid_handle(h));
                ++(handle_data_from_handle(h)._counter);
                erase_at(h.target_idx());
                VRM_CORE_ASSERT(!valid_handle(h));
            }
        };
    }

    template <typename TSignature>
    using dynamic_delegate = impl::dynamic_delegate<std::function, TSignature>;
}
VRM_CORE_NAMESPACE_END
