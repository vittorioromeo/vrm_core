// Copyright (c) 2015-2020 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <functional>
#include <vector>
#include <vrm/core/experimental/delegate/base_delegate.hpp>
#include <vrm/core/experimental/delegate/impl/dynamic_delegate.hpp>

namespace vrm::core
{
    namespace impl
    {
        template <typename TSettings>
        auto VRM_CORE_PURE_FN dynamic_delegate<TSettings>::next_fn_idx() const
            noexcept
        {
            return this->_functions.size() - 1;
        }

        template <typename TSettings>
        template <typename TF>
        auto dynamic_delegate<TSettings>::operator+=(TF&& f)
        {
            // Emplace function at the end of functions vector.
            this->emplace_function(FWD(f));

            // Return an handle to it.
            return _hm.create(next_fn_idx());
        }

        template <typename TSettings>
        void dynamic_delegate<TSettings>::operator-=(const handle_type& h)
        {
            _hm.destroy(h, [this](auto i) {
                // Swap dead function with last function in the vector.
                using std::swap;
                swap(this->_functions[i], this->_functions.back());

                // Pop back the dead function.
                this->_functions.pop_back();
            });
        }
    } // namespace impl
} // namespace vrm::core
