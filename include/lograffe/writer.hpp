//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <string>

namespace lograffe
{

	//
	// Common base class for writer implementations.
	//
	class writer
	{
	public:
		writer(const writer&) = delete;
		writer(writer&&) = default;

		virtual void write_line(const std::string&) = 0;

		virtual ~writer()
		{}

	protected:
		writer() = default;
	};

}
