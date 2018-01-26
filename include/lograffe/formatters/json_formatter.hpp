//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/formatter.hpp>
#include <lograffe/formatters/detail/logfmt_encoding.hpp>
#include <lograffe/formatters/detail/time_formatter.hpp>
#include <string>

namespace lograffe
{

	namespace formatters
	{

		class json_formatter : public formatter
		{
		public:
			json_formatter()
				: formatter()
			{}
		};

	}

}
