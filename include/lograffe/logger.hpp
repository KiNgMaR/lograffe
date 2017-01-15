//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/log_level.hpp>
#include <lograffe/log_entry.hpp>
#include <lograffe/sink.hpp>
#include <lograffe/formatter.hpp>
#include <vector>

namespace lograffe
{

	class logger
	{
	public:
		logger()
			: enabled_levels_()
		{}

		bool level_enabled(log_level level) const;
		void log(const log_entry& entry) noexcept;

		void attach_sink(std::unique_ptr<sink>&& new_sink);

		// to allow inline construction of sinks:
		template<class TSink, class TFormatter, class... TSinkArgs>
		void attach_sink(log_level min_level, TSinkArgs&&... args)
		{
			static_assert(std::is_base_of<sink, TSink>::value, "expecting type derived from lograffe::sink");
			static_assert(std::is_base_of<formatter, TFormatter>::value, "expecting type derived from lograffe::formatter");

			attach_sink(std::make_unique<TSink>(min_level, std::make_unique<TFormatter>(), std::forward<TSinkArgs>(args)...));
		}

	private:
		uint_fast32_t enabled_levels_; // contains a bitmask of all levels that are enabled on at least one sink
		std::vector<std::unique_ptr<sink>> sinks_;
	};

}
