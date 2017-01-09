//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/log_entry.hpp>
#include <string>

namespace lograffe
{

	class formatter
	{
	public:
		formatter(const formatter&) = default;
		formatter(formatter&&) = default;

		virtual std::string format_entry(const log_entry& entry) = 0;

		virtual ~formatter()
		{}

	protected:
		formatter() = default;
	};

}
