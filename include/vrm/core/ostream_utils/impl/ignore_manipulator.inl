// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <ostream>
#include <vrm/core/ostream_utils/impl/ignore_manipulator.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T>
        template <typename TStr>
        ignore_manipulator<T>::ignore_manipulator(TStr&& str)
            : _str(FWD(str))
        {
        }

        template <typename T>
        template <typename TStr>
        auto& ignore_manipulator<T>::operator=(TStr&& str)
        {
            _str = FWD(str);
            return *this;
        }

        template <typename T>
        ignore_manipulator<T>::operator const T&() const noexcept
        {
            return _str;
        }

        template <typename T>
        auto ignore_manipulator<T>::begin() const noexcept
        {
            return std::begin(_str);
        }

        template <typename T>
        auto ignore_manipulator<T>::end() const noexcept
        {
            return std::end(_str);
        }
    }

    template <typename T>
    auto make_ignore_manipulator(T && x)
    {
        return impl::ignore_manipulator<decltype(x)>(FWD(x));
    }

    template <typename T>
    auto operator<<(std::ostream & o, const T& im)
        ->std::enable_if_t<impl::is_ignore_manipulator<T>{}, std::ostream&>
    {
        for(const auto& c : im) o.put(c);
        return o;
    }
}
VRM_CORE_NAMESPACE_END
