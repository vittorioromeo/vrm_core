// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <utility>
#include <vrm/core/config.hpp>
#include <vrm/core/type_traits/nonesuch.hpp>
#include <vrm/core/type_traits/void_t.hpp>

// From:
// http://en.cppreference.com/w/cpp/experimental/is_detected

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <
            // Default type used if detection fails.
            typename TDefault,

            // Always `void`. This would ideally be a default template parameter
            // if possible, but there's a variadic pack.
            typename TVoid,

            // Operation to detect. `void_t<TOp<Ts...>>` will be used.
            template <typename...> class TOp, typename... Ts // .
            >
        struct detector
        {
            using value_t = std::false_type;
            using type = TDefault;
        };

        template <                            // .
            typename TDefault,                // .
            template <typename...> class TOp, // .
            typename... Ts                    // .
            >
        struct detector<TDefault, void_t<TOp<Ts...>>, TOp, Ts...>
        {
            using value_t = std::true_type;
            using type = TOp<Ts...>;
        };
    }

    template <template <typename...> class TOp, typename... Ts>
    using is_detected =
        typename impl::detector<nonesuch, void, TOp, Ts...>::value_t;

    template <template <typename...> class TOp, typename... Ts>
    using detected_t =
        typename impl::detector<nonesuch, void, TOp, Ts...>::type;

    template <typename TDefault, template <typename...> class TOp,
        typename... Ts>
    using detected_or = impl::detector<TDefault, void, TOp, Ts...>;

    template <template <typename...> class TOp, typename... Ts>
    constexpr bool is_detected_v = is_detected<TOp, Ts...>::value;

    template <typename TDefault, template <typename...> class TOp,
        typename... Ts>
    using detected_or_t = typename detected_or<TDefault, TOp, Ts...>::type;

    template <typename Expected, template <typename...> class TOp,
        typename... Ts>
    using is_detected_exact = std::is_same<Expected, detected_t<TOp, Ts...>>;

    template <typename Expected, template <typename...> class TOp,
        typename... Ts>
    constexpr bool is_detected_exact_v =
        is_detected_exact<Expected, TOp, Ts...>::value;

    template <typename To, template <typename...> class TOp, typename... Ts>
    using is_detected_convertible =
        std::is_convertible<detected_t<TOp, Ts...>, To>;

    template <typename To, template <typename...> class TOp, typename... Ts>
    constexpr bool is_detected_convertible_v =
        is_detected_convertible<To, TOp, Ts...>::value;
}
VRM_CORE_NAMESPACE_END
