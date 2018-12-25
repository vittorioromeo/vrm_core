// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/integral_constant.hpp>
#include <vrm/core/experimental/resource/base.hpp>

namespace vrm::core
{
    namespace resource
    {
        namespace impl
        {
            template <typename TBehavior>
            class unique : public impl::base<TBehavior>
            {
            public:
                using this_type = unique<TBehavior>;
                using base_type = impl::base<TBehavior>;
                using behavior_type = typename base_type::behavior_type;
                using handle_type = typename base_type::handle_type;

            private:
                using is_nothrow_deinit = is_nothrow_deinit_t<TBehavior>;

            public:
                /// @brief Deinitializes the stored handle and sets stored
                /// handle to `null_handle`.
                void reset() noexcept(is_nothrow_deinit{});

                /// @brief Deinitializes the stored handle and sets stored
                /// handle to `handle`.
                void reset(const handle_type& handle) noexcept(
                    is_nothrow_deinit{});

                ~unique() noexcept(is_nothrow_deinit{});

                constexpr unique() noexcept = default;
                explicit unique(const handle_type& handle) noexcept;

                // Disable copy operations.
                unique(const unique&) = delete;
                unique& operator=(const unique&) = delete;

                /// @brief Takes ownership of `rhs`'s handle. `rhs` will point
                /// to null.
                unique(unique&& rhs) noexcept;

                /// @brief Deinitializes the stored handle and takes ownership
                /// of `rhs`'s handle. `rhs` will point to null.
                auto& operator=(unique&&) noexcept(is_nothrow_deinit{});

                /// @brief Loses ownership of the stored handle and returns it.
                /// The handle is not deinitialized.
                auto release() noexcept;

                /// @brief Swaps the stored handle with `rhs`'s handle.
                void swap(unique& rhs) noexcept;

                /// @brief Returns `true` if both `lhs` and `rhs` store the same
                /// handle.
                template <typename>
                friend bool operator==(
                    const unique& lhs, const unique& rhs) noexcept;

                /// @brief Returns `true` if `lhs` and `rhs` store different
                /// handles.
                template <typename>
                friend bool operator!=(
                    const unique& lhs, const unique& rhs) noexcept;

                template <typename>
                friend void swap(unique& lhs, unique& rhs) noexcept;
            };
        }

        using impl::unique;
    }
}
