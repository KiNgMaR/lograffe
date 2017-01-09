//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/logger.hpp>

namespace lograffe
{

	inline bool logger::level_enabled(log_level level) const
	{
		return (enabled_levels_ & static_cast<decltype(enabled_levels_)>(level)) != 0;
	}

	inline void logger::log(const log_entry& entry) noexcept
	{
		// the buffer should be here
	}

}
