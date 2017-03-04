// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/integral_constant.hpp>
#include <vrm/core/type_traits/void_t.hpp>

VRM_CORE_NAMESPACE
{
    namespace resource
    {
        template <typename TBehavior>
        using is_nothrow_init_t = bool_<noexcept(TBehavior::init())>;

        template <typename TBehavior>
        using is_nothrow_deinit_t = bool_<noexcept(TBehavior::deinit(
            std::declval<typename TBehavior::handle_type>()))>;

        template <typename T>
        using is_zero_sized = std::integral_constant<bool, sizeof(T) == 1>;

        template <typename T, typename = void>
        struct has_init : std::false_type
        {
        };

        template <typename T>
        struct has_init<T, void_t<decltype(&T::init)>> : std::true_type
        {
        };

        template <typename T>
        using is_valid_behavior = std::integral_constant<bool, // .
            is_zero_sized<T>{} && has_init<T>{}                // .
            >;
    }
}
VRM_CORE_NAMESPACE_END

// TODO: use is_valid ?
// TODO: check other methods
