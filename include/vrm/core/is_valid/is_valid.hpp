// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>

namespace vrm::core
{
    namespace impl
    {
        struct is_valid_dummy
        {
        };

        template <typename T>
        class is_valid_wrapper
        {
        private:
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr auto test(is_valid_dummy) noexcept
                -> decltype(
                    std::declval<T>()(std::declval<Ts>()...), std::true_type{})
            {
                return std::true_type{};
            }

            template <typename...>
            VRM_CORE_ALWAYS_INLINE constexpr auto test(...) noexcept
            {
                return std::false_type{};
            }

        public:
            template <typename... Ts>
            VRM_CORE_ALWAYS_INLINE constexpr auto operator()(
                Ts&&... xs) noexcept
            {
                return test<decltype(xs)...>(is_valid_dummy{});
            }
        };
    }

    template <typename T>
    VRM_CORE_ALWAYS_INLINE constexpr auto is_valid(T && )
    {
        return impl::is_valid_wrapper<T>{};
    }
}
