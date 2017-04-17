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
#include <lograffe/detail/thread_local_static_instance.hpp>
#include <vector>
#include <functional>

namespace lograffe
{

	class logger : public detail::thread_local_static_instance<logger>
	{
	public:
		// default constructed = no-op logger
		logger()
			: enabled_levels_()
		{}

		// disallow copy construction and copy assignment
		logger(const logger&) = delete;
		logger(logger&&) = default;
		logger& operator=(const logger&) = delete;
		logger& operator=(logger&&) = default;

	public:
		typedef std::hash<void*>::result_type attached_sink_handle;

		attached_sink_handle attach_sink(std::unique_ptr<sink>&& new_sink);

		// to allow inline construction of sinks:
		template<class TSink, class TFormatter, class... TSinkArgs>
		attached_sink_handle attach_sink(log_level min_level, TSinkArgs&&... args)
		{
			static_assert(std::is_base_of<sink, TSink>::value, "expecting type derived from lograffe::sink");
			static_assert(std::is_base_of<formatter, TFormatter>::value, "expecting type derived from lograffe::formatter");

			return attach_sink(std::make_unique<TSink>(min_level, std::make_unique<TFormatter>(), std::forward<TSinkArgs>(args)...));
		}

		void detach_sink(attached_sink_handle handle);

	public:
		bool level_enabled(log_level level) const;
		void log(const log_entry& entry) noexcept;

	private:
		uint_fast32_t enabled_levels_; // contains a bitmask of all levels that are enabled on at least one sink
		std::vector<std::unique_ptr<sink>> sinks_;
	};

}
