// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <array>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_aliases.hpp>
#include <vrm/core/casts.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        namespace sparse_set_storage
        {
            template <         // .
                typename T,    // .
                sz_t TCapacity // .
                >
            class fixed_array
            {
            public:
                using value_type = T;
                static constexpr auto capacity = TCapacity;

            private:
                std::array<T, capacity> _dense;
                std::array<T*, capacity> _sparse;
                T* _end;

                auto last_element_ptr() noexcept
                {
                    return _end - 1;
                }

                auto last_element_ptr() const noexcept
                {
                    return _end - 1;
                }

            public:
                fixed_array()
                {
                    clear();
                }

                fixed_array(const fixed_array&) = delete;
                fixed_array& operator=(const fixed_array&) = delete;

                fixed_array(fixed_array&&) = delete;
                fixed_array& operator=(fixed_array&&) = delete;

                void clear() noexcept
                {
                    for(auto& p : _sparse)
                    {
                        p = nullptr;
                    }

                    _end = _dense.data();
                }

                bool has(const T& x) const noexcept
                {
                    VRM_CORE_ASSERT_OP(x, <, capacity);
                    return _sparse[x] != nullptr;
                }

                bool add(const T& x) noexcept
                {
                    VRM_CORE_ASSERT_OP(x, <, capacity);
                    if(has(x)) return false;

                    VRM_CORE_ASSERT_OP(size(), <, capacity);
                    *_end = x;

                    _sparse[x] = _end;
                    ++_end;

                    return true;
                }

                bool erase(const T& x) noexcept
                {
                    VRM_CORE_ASSERT_OP(x, <, capacity);
                    if(!has(x)) return false;

                    auto& ptr(_sparse[x]);
                    VRM_CORE_ASSERT_OP(size(), >, 0);

                    auto last(back());
                    VRM_CORE_ASSERT_OP(ptr, !=, nullptr);

                    if(*ptr != last)
                    {
                        *ptr = last;
                        _sparse[last] = ptr;
                    }

                    VRM_CORE_ASSERT(has(x));
                    ptr = nullptr;

                    VRM_CORE_ASSERT_OP(size(), >, 0);
                    --_end;

                    return true;
                }


                bool empty() const noexcept
                {
                    return _end == _dense.data();
                }

                void pop_back() noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), >, 0);
                    erase(back());
                }

                auto back() const noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), >, 0);

                    VRM_CORE_ASSERT(has(*(last_element_ptr())));
                    return *(last_element_ptr());
                }

                template <typename TF>
                void for_each(TF&& f) const noexcept
                {
                    VRM_CORE_ASSERT_OP(size(), <=, capacity);

                    for(auto p(_dense.data()); p != _end; ++p)
                    {
                        VRM_CORE_ASSERT(has(*p));
                        f(*p);
                    }
                }

                auto size() const noexcept
                {
                    return to_sz_t(end() - begin());
                }

                auto begin() noexcept
                {
                    return _dense.data();
                }

                auto begin() const noexcept
                {
                    return _dense.data();
                }

                auto end() noexcept
                {
                    return _end;
                }

                auto end() const noexcept
                {
                    return static_cast<const T*>(_end);
                }

                auto& operator[](sz_t i) noexcept
                {
                    VRM_CORE_ASSERT_OP(i, <, size());
                    return _dense[i];
                }

                const auto& operator[](sz_t i) const noexcept
                {
                    VRM_CORE_ASSERT_OP(i, <, size());
                    return _dense[i];
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
