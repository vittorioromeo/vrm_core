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
#include <vrm/core/strong_typedef.hpp>

// TODO: WIP:
// * use sparse int set?

// TODO:
// Strong handle typedefs for index/target

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TTarget, typename TCounter>
        class handle_settings
        {
        public:
            // From metadata to target user-specified object.
            using target_type = TTarget;

            // Counter type.
            using counter_type = TCounter;

        private:
            struct metadata_impl
            {
                target_type _target;
                counter_type _counter{0};
            };

            template <typename TMetadataRef>
            struct handle_impl
            {
                TMetadataRef _metadata_ref;
                counter_type _counter{0};
            };


        public:
            using metadata_type = metadata_impl;

            template <typename TMetadataRef>
            using handle_type = handle_impl<TMetadataRef>;
        };

        namespace handle_storage
        {
            // Fixed array, uses ptrs as metadata refs
            template <typename TSettings, sz_t TCount>
            class hs_array
            {
            public:
                using settings_type = TSettings;
                using target_type = typename settings_type::target_type;
                using counter_type = typename settings_type::counter_type;
                using metadata_type = typename settings_type::metadata_type;
                using metadata_ref_type = metadata_type*;

                using handle_type =
                    typename settings_type::template handle_type<
                        metadata_ref_type>;

                static constexpr sz_t count{TCount};

            private:
                std::array<metadata_type, count> _metadata;
                metadata_ref_type _next_ref{_metadata.data()};

            public:
                auto& metadata_from_handle(const handle_type& h) noexcept
                {
                    return *(h._metadata_ref);
                }

                const auto& metadata_from_handle(const handle_type& h) const
                    noexcept
                {
                    return *(h._metadata_ref);
                }

                auto create(const target_type& target)
                {
                    // Out of the array.
                    VRM_CORE_ASSERT_OP(_next_ref, !=, _metadata.data() + count);

                    // Get ptr and increment next ptr.
                    auto m_ref(_next_ref);
                    ++_next_ref;

                    // Set it to desired target.
                    m_ref->_target = target;

                    // Return handle.
                    return handle_type{m_ref, m_ref->_counter};
                }

                // TODO:
                template <typename TF>
                void destroy(const handle_type& h, TF&& f)
                {
                    // Get corresponding metadata and invalidate it.
                    auto& m(metadata_from_handle(h));
                    ++(m._counter);

                    // Get last metadata.
                    auto last_m_ref(_next_ref - 1);

                    // Call target cleanup function. (TODO: ?)
                    f(m._target);

                    // Swap indices and `pop_back` (TODO:)
                    std::swap(m._target, last_m_ref->_target);
                    --_next_ref;
                }
            };

            // Resizable array, uses idxs as metadata refs
            template <typename TSettings>
            class hs_vector
            {
            public:
                using settings_type = TSettings;
                using target_type = typename settings_type::target_type;
                using counter_type = typename settings_type::counter_type;
                using metadata_type = typename settings_type::metadata_type;
                using metadata_ref_type = sz_t;

                using handle_type =
                    typename settings_type::template handle_type<
                        metadata_ref_type>;

            private:
                std::vector<metadata_type> _metadata;
                metadata_ref_type _next_ref{0};

                void assert_validity(const handle_type& h) const noexcept
                {
                    VRM_CORE_ASSERT_OP(h._metadata_ref, >=, 0);
                    VRM_CORE_ASSERT_OP(h._metadata_ref, <, _metadata.size());
                }

                void grow_if_needed()
                {
                    if(_next_ref < _metadata.size()) return;
                    _metadata.resize(_metadata.size() + 100);
                }

            public:
                auto& metadata_from_handle(const handle_type& h) noexcept
                {
                    assert_validity(h);
                    return _metadata[h._metadata_ref];
                }

                const auto& metadata_from_handle(const handle_type& h) const
                    noexcept
                {
                    assert_validity(h);
                    return _metadata[h._metadata_ref];
                }

                auto create(const target_type& target)
                {
                    grow_if_needed();

                    // Get ptr and increment next ptr.
                    auto m_ref(_next_ref);
                    ++_next_ref;

                    // Reference to new metadata.
                    auto& m(_metadata[m_ref]);

                    // Set it to desired target.
                    m._target = target;

                    // Return handle.
                    return handle_type{m_ref, m._counter};
                }

                template <typename TF>
                void destroy(const handle_type& h, TF&& f)
                {
                    // Get corresponding metadata and invalidate it.
                    auto& m(metadata_from_handle(h));
                    ++(m._counter);

                    // Get last metadata.
                    auto& last_m(_metadata[_next_ref - 1]);

                    // Call target cleanup function. (TODO: ?)
                    f(m._target);

                    // Swap indices and `pop_back` (TODO:)
                    std::swap(m._target, last_m._target);
                    --_next_ref;
                }
            };
        }

        template <typename TStorage>
        class handle_manager
        {
        public:
            using storage_type = TStorage;
            using counter_type = typename storage_type::counter_type;
            using handle_type = typename storage_type::handle_type;
            using target_type = typename storage_type::target_type;
            using metadata_type = typename storage_type::metadata_type;
            using metadata_ref_type = typename storage_type::metadata_ref_type;

        private:
            storage_type _storage;

        public:
            VRM_CORE_ALWAYS_INLINE auto valid_handle(const handle_type& h) const
                noexcept
            {
                return h._counter == _storage.metadata_from_handle(h)._counter;
            }

            auto create(const target_type& target)
            {
                auto h(_storage.create(target));
                VRM_CORE_ASSERT(valid_handle(h));
                return h;
            }

            // TODO:
            template <typename TF>
            void destroy(const handle_type& h, TF&& f)
            {
                VRM_CORE_ASSERT(valid_handle(h));
                _storage.destroy(h, FWD(f));
                VRM_CORE_ASSERT(!valid_handle(h));
            }
        };


        using index_type = sz_t;
        using counter_type = std::int8_t;

        using test_hs = handle_settings<index_type, counter_type>;

        using test_st = handle_storage::hs_array<test_hs, 100>;
        // using test_st = handle_storage::hs_vector<test_hs>;

        using test_hm = handle_manager<test_st>;

        template <template <typename...> class TFunction, typename TSignature>
        class VRM_CORE_CLASS_API dynamic_delegate
            : public impl::base_delegate<TFunction, TSignature>
        {
        public:
            using hm_type = test_hm;
            using metadata_type = typename hm_type::metadata_type;
            using handle_type = typename hm_type::handle_type;

        private:
            using base_type = impl::base_delegate<TFunction, TSignature>;
            hm_type _hm;

        public:
            using fn_type = typename base_type::fn_type;

        private:
            auto next_fn_idx() const noexcept
            {
                return this->_functions.size() - 1;
            }

        public:
            template <typename TF>
            auto operator+=(TF&& f)
            {
                // Emplace function at the end of functions vector.
                this->emplace_function(FWD(f));

                // Return an handle to it.
                return _hm.create(next_fn_idx());
            }

            void operator-=(const handle_type& h)
            {
                _hm.destroy(h, [this](auto i)
                    {
                        // Swap dead function with last function in the vector.
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
