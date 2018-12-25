// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/utility_macros.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/handle2/settings.hpp>

namespace vrm::core
{
    namespace handle2
    {
        template <typename TSettings, typename TDerived>
        class context
        {
        public:
            using settings_type = TSettings;
            using handle_data_type = aliases::handle_data_type<settings_type>;
            using target_type = aliases::target_type<settings_type>;
            using counter_type = aliases::counter_type<settings_type>;
            using handle_type = aliases::handle_type<settings_type>;

        private:
            auto& derived() noexcept
            {
                return static_cast<TDerived&>(*this);
            }
            const auto& derived() const noexcept
            {
                return static_cast<const TDerived&>(*this);
            }

        protected:
            auto& counter(const handle_data_type& hd)
            {
                return derived().counter(hd);
            }
            const auto& counter(const handle_data_type& hd) const
            {
                return derived().counter(hd);
            }

            const auto& data(const handle_type& h) const noexcept
            {
                return h._data;
            }
            const auto& local_counter(const handle_type& h) const noexcept
            {
                return h._counter;
            }

        public:
            auto valid(const handle_type& h) const
            {
                return counter(data(h)) == local_counter(h);
            }

            auto create_handle_from_data(const handle_data_type& hd)
            {
                handle_type result{hd, counter(hd)};
                VRM_CORE_ASSERT(valid(result));
                return result;
            }

        protected:
            void invalidate(const handle_data_type& hd)
            {
                ++(counter(hd));
            }
        };
    }
}
