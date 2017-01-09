//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/log_entry.hpp>

namespace lograffe
{

	// because of our clever syntax with LOG(), the best way to flush this entry to
	// the logger is to do it from the destructor:
	inline log_entry::~log_entry()
	{
		logger_instance_.log(*this);
	}

}
