// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/assert.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/integral_constant.hpp>
#include <vrm/core/type_traits.hpp>

#include <cfenv>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace vrm::core::impl
{
    template <typename TOut, typename TIn>
    [[nodiscard]] constexpr bool will_overflow_impl(const TIn& x,
        std::false_type /* `TOut` is integral */,
        std::false_type /* `TIn` is integral */) noexcept
    {
        if(x > std::numeric_limits<TOut>::max() ||
            x < std::numeric_limits<TOut>::lowest())
        {
            return true;
        }

        std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID);

        TOut temp0(x);
        TIn temp1(x);
        temp0 = temp1;
        (void)temp0;
        (void)temp1;

        if(std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID))
        {
            return true;
        }

        // Sanity check.
        if(static_cast<TIn>(static_cast<TOut>(x)) != x)
        {
            return true;
        }

        return false;
    }

    template <typename TOut, typename TIn>
    [[nodiscard]] constexpr bool will_overflow_impl(const TIn& x,
        std::true_type /* `TOut` is integral */,
        std::false_type /* `TIn` is integral */) noexcept
    {
        return (long double)x > (long double)std::numeric_limits<TOut>::max() ||
               (long double)x <
                   (long double)std::numeric_limits<TOut>::lowest();
    }

    template <typename TOut, typename TIn>
    [[nodiscard]] constexpr bool will_overflow_impl(const TIn& x,
        std::false_type /* `TOut` is integral */,
        std::true_type /* `TIn` is integral */) noexcept
    {
        return (long double)x > (long double)std::numeric_limits<TOut>::max() ||
               (long double)x <
                   (long double)std::numeric_limits<TOut>::lowest();
    }

    template <typename TOut, typename TIn>
    [[nodiscard]] constexpr bool will_overflow_impl(const TIn& x,
        std::true_type /* `TOut` is integral */,
        std::true_type /* `TIn` is integral */) noexcept
    {
        using out_lim = std::numeric_limits<TOut>;
        using intmax_lim = std::numeric_limits<intmax_t>;

        constexpr auto out_min(out_lim::min());
        constexpr auto out_max(out_lim::max());
        constexpr auto intmax_max(intmax_lim::max());

        auto x_as_intmax_t(static_cast<intmax_t>(x));
        auto x_as_uintmax_t(static_cast<uintmax_t>(x));

        constexpr auto out_min_as_intmax_t(static_cast<intmax_t>(out_min));
        constexpr auto out_max_as_intmax_t(static_cast<intmax_t>(out_max));

        constexpr auto intmax_max_as_uintmax_t(
            static_cast<uintmax_t>(intmax_max));

        constexpr auto out_max_as_uintmax_t(static_cast<uintmax_t>(out_max));

        if(std::is_signed<TOut>{})
        {
            // The output type is signed, the input type is unsigned, and
            // the "uintmax-casted input" is bigger than the "uintmax-casted
            // intmax".
            if(!std::is_signed<TIn>{} &&
                x_as_uintmax_t > intmax_max_as_uintmax_t)
            {
                return true;
            }

            // The output type is signed, the input type is unsigned, and
            // the "intmax-casted input" is smaller than the "intmax-casted
            // output minimum".
            if(x_as_intmax_t < out_min_as_intmax_t)
            {
                return true;
            }

            // The output type is signed, the input type is unsigned, and
            // the "intmax-casted input" is bigger than the "intmax-casted
            // output maximum".
            if(x_as_intmax_t > out_max_as_intmax_t)
            {
                return true;
            }

            return false;
        }

        // The output type is unsigned, and `x` is negative.
        if(x < 0)
        {
            return true;
        }

        // The output type is unsigned, and the "uintmax-casted input" is
        // bigger than the "uintmax-casted output maximum".
        if(x_as_uintmax_t > out_max_as_uintmax_t)
        {
            return true;
        }

        // Sanity check.
        if(static_cast<TIn>(static_cast<TOut>(x)) != x)
        {
            return true;
        }

        return false;
    }

    template <typename TOut, typename TIn>
    [[nodiscard]] constexpr bool will_overflow(const TIn& x) noexcept
    {
        return will_overflow_impl<TOut, TIn>(x,
            bool_v<std::is_integral_v<TOut>>, bool_v<std::is_integral_v<TIn>>);
    }
} // namespace vrm::core::impl
