// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <type_traits>
#include <vrm/core/perfect_wrapper.hpp>
#include <vrm/core/utility_macros/fwd.hpp>

namespace vrm::core::impl
{
    template <typename T>
    class fwd_capture_wrapper : public perfect_wrapper<T>
    {
    private:
        using base_type = perfect_wrapper<T>;

    public:
        template <typename TFwd>
        explicit constexpr fwd_capture_wrapper(TFwd&& x) noexcept(
            std::is_nothrow_constructible<base_type, TFwd&&>{})
            : base_type(FWD(x))
        {
        }

        /// @brief Gets the wrapped perfectly-captured object by forwarding
        /// it into the return value.
        /// @details Returns `std::forward<T>(this->get())`. In practice:
        /// * If the wrapped object is a value, it gets moved out (instead
        /// of returning a reference to it like `get()` would).
        /// * If the wrapped object is a reference, a reference gets
        /// returned.
        /// This happens because `T` is a reference type.
        constexpr T fwd_get() noexcept(std::is_nothrow_constructible<T, T&&>{})
        {
            // Note: `FWD` is not applicable here.
            return std::forward<T>(this->get());
        }

        constexpr T fwd_get() const = delete;
    };

    template <typename T>
    constexpr auto fwd_capture(T&& x) noexcept(
        noexcept(fwd_capture_wrapper<T>(FWD(x))))
    {
        return fwd_capture_wrapper<T>(FWD(x));
    }

    template <typename T>
    constexpr auto fwd_copy_capture(T&& x) noexcept(
        noexcept(fwd_capture_wrapper<T>(x)))
    {
        return fwd_capture_wrapper<T>(x);
    }
} // namespace vrm::core::impl

#define VRM_CORE_FWD_CAPTURE(...) \
    ::vrm::core::impl::fwd_capture(FWD(__VA_ARGS__))

#define VRM_CORE_FWD_COPY_CAPTURE(...) \
    ::vrm::core::impl::fwd_copy_capture(FWD(__VA_ARGS__))

#if !defined(VRM_CORE_NO_FWD_CAPTURE_MACRO) && !defined(FWD_CAPTURE)
#define FWD_CAPTURE VRM_CORE_FWD_CAPTURE
#endif

#if !defined(VRM_CORE_NO_FWD_COPY_CAPTURE_MACRO) && !defined(FWD_COPY_CAPTURE)
#define FWD_COPY_CAPTURE VRM_CORE_FWD_COPY_CAPTURE
#endif
