// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/experimental/resource/behavior.hpp>
#include <vrm/core/experimental/resource/fwd.hpp>

namespace vrm::core
{
    namespace resource
    {
        namespace impl
        {
            /// @brief Base resource class containing shared logic and state
            /// between
            /// multiple resource types.
            /// @details Provides `behavior_type` and `handle_type` type
            /// aliases.
            /// Provides a static `null_handle` shortcut method.
            /// Contains a single `handle_type _handle` instance.
            /// Defines a default constructor and an `explicit` constructor that
            /// taken an handle.
            /// Provides shortcut methods to `deinit`, `nullify`, and `release`.
            /// Provides a `get` method and `bool` conversions.
            template <typename TBehavior>
            class base
            {
                template <typename, typename>
                friend class weak;

            public:
                using behavior_type = TBehavior;
                using handle_type = typename behavior_type::handle_type;

            private:
                static auto null_handle() noexcept;

            protected:
                handle_type _handle;

                base() noexcept;
                explicit base(const handle_type& handle) noexcept;

                [[nodiscard]] auto is_null_handle() const noexcept;

                void deinit() noexcept(is_nothrow_deinit_t<TBehavior>{});
                void nullify() noexcept;
                auto release_and_nullify() noexcept;

                void swap(base& rhs) noexcept;

            public:
                [[nodiscard]] auto get() const noexcept;
                explicit operator bool() const noexcept;
            };
        } // namespace impl
    }     // namespace resource
} // namespace vrm::core
