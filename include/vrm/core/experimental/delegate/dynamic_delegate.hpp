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
            class handle_data
            {
            private:
                index_type _index;
                counter_type _counter;

            public:
                VRM_CORE_ALWAYS_INLINE handle_data(index_type index,
                    counter_type counter) noexcept : _index{index},
                                                     _counter{counter}
                {
                }
            };

            struct metadata_impl : handle_data
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

            struct handle_impl : handle_data
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
            std::vector<metadata_type> _metadata;
            sz_t _next_idx{0};

            // Get metadata from existing handle.
            template <typename TSelf>
            VRM_CORE_ALWAYS_INLINE static decltype(auto)
            metadata_from_handle_impl(
                TSelf&& self, const handle_type& h) noexcept
            {
                VRM_CORE_ASSERT_OP(self.metadata.size(), >, h.target_idx());
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

            auto create()
            {
                auto idx(_next_idx);
                ++_next_idx;

                // Grow if needed.
                if(idx > _metadata.size())
                {
                    _metadata.resize(_metadata.size() + 100);
                }

                // Handle points above. (TODO: generalize)
                _metadata[idx]._index = idx;

                handle_type h{idx, _metadata[idx]._counter};
                VRM_CORE_ASSERT(valid_handle(h));

                return h;
            }

            void destroy(const handle_type& h)
            {
                VRM_CORE_ASSERT(valid_handle(h));

                // Get corresponding metadata and invalidate it.
                auto& m(metadata_from_handle(h));
                ++(m._counter);

                // Swap indices and `pop_back` (TODO:)
                auto& last_m(_metadata[_next_idx]);
                std::swap(m._index, last_m._index);
                --_next_idx;

                VRM_CORE_ASSERT(!valid_handle(h));
            }
        };

        using index_type = sz_t;
        using counter_type = std::int8_t;

        using test_hh = handle_helper<index_type, counter_type>;

        struct handle_data
        {
            index_type _index;
            counter_type _counter;

            // TODO: meh
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
                // VRM_CORE_ASSERT_OP(this->_functions.size(), >, idx);
                // this->_functions.erase(std::begin(this->_functions) + idx);

                auto to_erase_idx(idx);
                auto last_idx(this->_functions.size() - 1);

                auto& to_erase(this->_functions[to_erase_idx]);
                auto& last(this->_functions[last_idx]);

                auto& to_erase_handle(_handle_data[to_erase_idx]);
                auto& last_handle(_handle_data[last_idx]);

                std::swap(to_erase, last);
                std::swap(to_erase_handle._index, last_handle._index);

                this->_functions.pop_back();
            }

        public:
            using fn_type = typename base_type::fn_type;

        public:
            template <typename TF>
            auto operator+=(TF&& f)
            {
                auto idx(this->_functions.size());
                this->emplace_function(FWD(f));

                // TODO: meh
                _handle_data.resize(this->_functions.size());
                _handle_data[idx]._index = idx;

                handle_type h{idx, _handle_data[idx]._counter};
                VRM_CORE_ASSERT(valid_handle(h));

                return h;
            }

            void operator-=(const handle_type& h)
            {
                VRM_CORE_ASSERT(valid_handle(h));
                auto& metadata(handle_data_from_handle(h));
                ++(metadata._counter);
                erase_at(metadata._index);
                VRM_CORE_ASSERT(!valid_handle(h));
            }
        };
    }

    template <typename TSignature>
    using dynamic_delegate = impl::dynamic_delegate<std::function, TSignature>;
}
VRM_CORE_NAMESPACE_END
