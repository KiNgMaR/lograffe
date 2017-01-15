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
		return static_cast<uint_fast32_t>(level) >= enabled_levels_;
	}

	inline void logger::attach_sink(std::unique_ptr<sink>&& new_sink)
	{
		if (!new_sink)
		{
			return;
		}

		sinks_.emplace_back(std::move(new_sink));

		uint_fast32_t new_levels{};

		for (const auto& sink_ptr : sinks_)
		{
			new_levels = new_levels | static_cast<uint_fast32_t>(sink_ptr->min_level());
		}

		enabled_levels_ = new_levels;
	}

	inline void logger::log(const log_entry& entry) noexcept
	{
		for (auto& sink_ptr : sinks_)
		{
			sink_ptr->push(entry);
		}
	}

}
