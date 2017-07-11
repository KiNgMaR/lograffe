//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/sink.hpp>
#include <mutex>

namespace lograffe
{

namespace sinks
{

	// This class implements a sink that doesn't do anything. It
	// simply discards all log entries.
	class null_sink : public sink
	{
	public:
		null_sink(log_level min_level)
			: sink(min_level)
		{}

		void push(const log_entry& entry) override
		{
		}
	};

}

}
