// Copyright (c) 2015-2019 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#include <ostream>
#include <vrm/core/ostream_utils/nullptr_printer.hpp>

namespace std
{
    auto& operator<<(std::ostream& o, const std::nullptr_t&)
    {
        o << "nullptr";
        return o;
    }
}
