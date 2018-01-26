//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/formatters/detail/utf8_dfa.hpp>
#include <string>
#include <sstream>
#include <iomanip>

namespace lograffe
{

namespace formatters
{

namespace detail
{

    // Simplistic json encoder. Expects UTF-8 encoded strings and replaces invalid UTF-8 with a unicode substitution character.
    class json_encoding
    {
    public:

    };

}

}

}
