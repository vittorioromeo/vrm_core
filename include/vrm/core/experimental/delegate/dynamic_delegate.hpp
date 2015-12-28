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

// TODO:
// Strong handle typedefs for index/target

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TIndex, typename TCounter>
        class handle_helper
        {
        public:
            using index_type = TIndex;
            using counter_type = TCounter;

        private:
            // TODO:
            struct handle_data
            {
                // TODO:
            public:
                // TODO: could be a pointer?
                index_type _index;


                counter_type _counter;

            public:
                // TODO:
                VRM_CORE_ALWAYS_INLINE handle_data() noexcept : _index{0},
                                                                _counter{0}
                {
                }

                VRM_CORE_ALWAYS_INLINE handle_data(index_type index,
                    counter_type counter) noexcept : _index{index},
                                                     _counter{counter}
                {
                }
            };

            struct metadata_impl : public handle_data
            {
                using handle_data::handle_data;

                VRM_CORE_ALWAYS_INLINE const auto& idx() const noexcept
                {
                    return this->_index;
                }


                VRM_CORE_ALWAYS_INLINE const auto& counter() const noexcept
                {
                    return this->_counter;
                }
            };

            struct handle_impl : public handle_data
            {
                using handle_data::handle_data;

                VRM_CORE_ALWAYS_INLINE const auto& target_idx() const noexcept
                {
                    return this->_index;
                }

                VRM_CORE_ALWAYS_INLINE const auto& counter() const noexcept
                {
                    return this->_counter;
                }
            };

        public:
            using handle_type = handle_impl;
            using metadata_type = metadata_impl;
        };

        template <typename THandleHelper>
        class handle_vector
        {
        private:
            using handle_helper_type = THandleHelper;

        public:
            using index_type = typename handle_helper_type::index_type;
            using counter_type = typename handle_helper_type::counter_type;
            using handle_type = typename handle_helper_type::handle_type;
            using metadata_type = typename handle_helper_type::metadata_type;

        private:
            // TODO: generalize container semantics, not vector
            std::vector<metadata_type> _metadata;
            sz_t _next_idx{0};

            // Get metadata from existing handle.
            template <typename TSelf>
            VRM_CORE_ALWAYS_INLINE static decltype(auto)
            metadata_from_handle_impl(
                TSelf&& self, const handle_type& h) noexcept
            {
                VRM_CORE_ASSERT_OP(self._metadata.size(), >, h.target_idx());
                return self._metadata[h.target_idx()];
            }

        public:
#define VRM_CORE_IMPL_DEFINE_METADATA_FROM_HANDLE(qualifier)    \
    VRM_CORE_ALWAYS_INLINE decltype(auto) metadata_from_handle( \
        const handle_type& h) qualifier noexcept                \
    {                                                           \
        return metadata_from_handle_impl(*this, h);             \
    }

            VRM_CORE_IMPL_DEFINE_METADATA_FROM_HANDLE(&)
            VRM_CORE_IMPL_DEFINE_METADATA_FROM_HANDLE(const&)
            VRM_CORE_IMPL_DEFINE_METADATA_FROM_HANDLE(&&)

#undef VRM_CORE_IMPL_DEFINE_METADATA_FROM_HANDLE

            VRM_CORE_ALWAYS_INLINE auto valid_handle(const handle_type& h) const
                noexcept
            {
                return h.counter() == metadata_from_handle(h).counter();
            }

            auto create(sz_t item_idx)
            {
                auto m_idx(_next_idx);
                ++_next_idx;

                // Grow if needed.
                if(m_idx >= _metadata.size())
                {
                    _metadata.resize(_metadata.size() + 100);
                }

                VRM_CORE_ASSERT_OP(m_idx, <, _metadata.size());

                // Handle points to item. (TODO: generalize)
                _metadata[m_idx]._index = item_idx;

                handle_type h{m_idx, _metadata[m_idx]._counter};
                VRM_CORE_ASSERT(valid_handle(h));

                return h;
            }

            // TODO:
            template <typename TF>
            void destroy(const handle_type& h, TF&& f)
            {
                VRM_CORE_ASSERT(valid_handle(h));

                // Get corresponding metadata and invalidate it.
                auto& m(metadata_from_handle(h));
                ++(m._counter);

                // Get last metadata.
                auto& last_m(_metadata[_next_idx - 1]);
                f(m._index);

                // Swap indices and `pop_back` (TODO:)
                std::swap(m._index, last_m._index);
                --_next_idx;

                VRM_CORE_ASSERT(!valid_handle(h));
            }
        };

        using index_type = sz_t;
        using counter_type = std::int8_t;

        using test_hh = handle_helper<index_type, counter_type>;

        template <template <typename...> class TFunction, typename TSignature>
        class VRM_CORE_CLASS_API dynamic_delegate
            : public impl::base_delegate<TFunction, TSignature>
        {
        public:
            using hv_type = handle_vector<test_hh>;
            using metadata_type = typename hv_type::metadata_type;
            using handle_type = typename hv_type::handle_type;

        private:
            using base_type = impl::base_delegate<TFunction, TSignature>;
            hv_type _hv;

        public:
            using fn_type = typename base_type::fn_type;

        public:
            template <typename TF>
            auto operator+=(TF&& f)
            {
                // auto idx(this->_functions.size());
                this->emplace_function(FWD(f));

                return _hv.create(this->_functions.size() - 1);
            }

            void operator-=(const handle_type& h)
            {
                _hv.destroy(h, [this](auto i)
                    {
                        std::swap(this->_functions[i], this->_functions.back());
                        this->_functions.pop_back();
                    });
            }
        };
    }

    template <typename TSignature>
    using dynamic_delegate = impl::dynamic_delegate<std::function, TSignature>;
}
VRM_CORE_NAMESPACE_END
