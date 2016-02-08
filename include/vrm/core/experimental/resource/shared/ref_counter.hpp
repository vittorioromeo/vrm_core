// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros/fwd.hpp>
#include <vrm/core/assert/assert.hpp>
#include <vrm/core/experimental/resource/shared/metadata.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        namespace impl
        {
            // TODO: test polymorphism with custom shared_ptr
            class shared_ref_counter
            {
            private:
                shared_metadata* _metadata{nullptr};

                auto& access_metadata() noexcept
                {
                    VRM_CORE_ASSERT(!is_null());
                    return *_metadata;
                }

                const auto& access_metadata() const noexcept
                {
                    VRM_CORE_ASSERT(!is_null());
                    return *_metadata;
                }

                auto weak_count() const noexcept
                {
                    return access_metadata().weak_count();
                }

                auto total_count() const noexcept
                {
                    return access_metadata().total_count();
                }

                auto has_any_ref() const noexcept
                {
                    return access_metadata().has_any_ref();
                }

                void increment_owner() noexcept
                {
                    access_metadata().increment_owner();
                }

                void decrement_owner() noexcept
                {
                    access_metadata().decrement_owner();
                }

                void deallocate() noexcept
                {
                    // TODO: total_count?
                    VRM_CORE_ASSERT_OP(access_metadata().owner_count(), ==, 0);
                    delete _metadata;
                }

                template <typename TF>
                void deallocate_if_required(TF&& deleter) noexcept
                {
                    if(!has_any_ref())
                    {
                        deleter();
                        deallocate();
                    }

                    _metadata = nullptr;
                }

                void decrement_weak() noexcept
                {
                    access_metadata().decrement_weak();
                }

            public:
                shared_ref_counter() noexcept = default;

                shared_ref_counter(const shared_ref_counter&) = default;
                shared_ref_counter& operator=(
                    const shared_ref_counter&) = default;

                shared_ref_counter(shared_ref_counter&& rhs) noexcept
                    : _metadata{rhs._metadata}
                {
                    rhs._metadata = nullptr;
                }

                auto& operator=(shared_ref_counter&& rhs) noexcept
                {
                    _metadata = rhs._metadata;
                    rhs._metadata = nullptr;
                    return *this;
                }

                bool is_null() const noexcept { return _metadata == nullptr; }

                auto owner_count() const noexcept
                {
                    return access_metadata().owner_count();
                }

                auto use_count() const noexcept
                {
                    // TODO: owner count?

                    return is_null() ? 0 : owner_count();
                }

                void acquire_from_null()
                {
                    VRM_CORE_ASSERT(is_null());
                    _metadata = new shared_metadata{1, 0};
                    // TODO: could throw `std::bad_alloc`.
                }

                void acquire_existing() noexcept
                {
                    VRM_CORE_ASSERT(!is_null());
                    increment_owner();
                }

                void increment_weak() noexcept
                {
                    access_metadata().increment_weak();
                }



                template <typename TF>
                void lose_ownership(TF&& deleter) noexcept
                {
                    decrement_owner();
                    deallocate_if_required(FWD(deleter));
                }

                template <typename TF>
                void lose_weak(TF&& deleter)
                {
                    decrement_weak();
                    deallocate_if_required(FWD(deleter));
                }
            };
        }
    }
}
VRM_CORE_NAMESPACE_END
