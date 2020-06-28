// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <vector>
#include <vrm/core/experimental/delegate/base_delegate.hpp>
#include <vrm/core/experimental/delegate/impl/delegate.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <typename TSettings>
        template <typename TF>
        void delegate<TSettings>::operator+=(TF&& f)
        {
            this->emplace_function(FWD(f));
        }
    } // namespace impl
} // namespace vrm::core
