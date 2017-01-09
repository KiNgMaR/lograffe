//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/log_level.hpp>
#include <lograffe/log_entry.hpp>

namespace lograffe
{

	class logger
	{
	public:
		bool level_enabled(log_level level) const;
		void log(const log_entry& entry) noexcept;

	private:
		uint_fast32_t enabled_levels_; // contains a bitmask of all levels that are enabled on at least one sink
	};

}
