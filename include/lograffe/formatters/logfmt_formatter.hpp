//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/formatter.hpp>
#include <string>

namespace lograffe
{

	namespace formatters
	{

		class logfmt_formatter : public formatter
		{
		public:
			logfmt_formatter()
				: formatter()
			{}
		};

	}

}
