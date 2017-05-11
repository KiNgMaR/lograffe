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

	inline logger::attached_sink_handle logger::attach_sink(const std::shared_ptr<sink>& new_sink)
	{
		if (!new_sink)
		{
			return attached_sink_handle();
		}

		attached_sink_handle new_sink_handle = std::hash<void*>()(new_sink.get());

		sinks_.emplace_back(std::move(new_sink));

		calculate_enabled_levels();

		return new_sink_handle;
	}

	inline void logger::detach_sink(attached_sink_handle handle)
	{
		// TODO: this is ugly

		const auto comparison = [handle](const auto& sink_ptr) -> bool
			{ return std::hash<void*>()(sink_ptr.get()) == handle; };

		sinks_.erase(
			std::remove_if(sinks_.begin(), sinks_.end(), comparison),
			sinks_.end());
		
		calculate_enabled_levels();
	}

	inline void logger::log(const log_entry& entry)
	{
		for (auto& sink_ptr : sinks_)
		{
			sink_ptr->push(entry);
		}
	}

	inline void logger::calculate_enabled_levels()
	{
		uint_fast32_t new_levels{};

		for (const auto& sink_ptr : sinks_)
		{
			new_levels = new_levels | static_cast<uint_fast32_t>(sink_ptr->min_level());
		}

		enabled_levels_ = new_levels;
	}

}
