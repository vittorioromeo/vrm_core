// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once


namespace vrm::core
{
    namespace impl
    {
        template <typename TSignature>
        struct signature_helper;

        template <typename TReturn, typename... TArgs>
        struct signature_helper<TReturn(TArgs...)>
        {
            using return_type = TReturn;
        };

        template <typename TSignature>
        using signature_return_type =
            typename signature_helper<TSignature>::return_type;
    } // namespace impl
} // namespace vrm::core
