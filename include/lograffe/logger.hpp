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
#include <memory>
#include <functional>

namespace lograffe
{

	class logger : public detail::thread_local_static_instance<logger>
	{
	public:
		// default constructed = no-op logger
		logger()
			: enabled_levels_() // TODO: fix default level and/or level_enabled
			, sinks_()
		{}

		// provided by parent class:
		// static logger& current();
		// static void set_current(logger&&);
		// static void reset_current();
		// static void set_global_default_creation_method(std::function<std::unique_ptr<logger> ()>);

		// disallow copy construction and copy assignment
		logger(const logger&) = delete;
		logger(logger&&) = default;
		logger& operator=(const logger&) = delete;
		logger& operator=(logger&&) = default;

	public:
        class attached_sink_handle
        {
        public:
            attached_sink_handle()
                : ptr_(nullptr)
            {}
            attached_sink_handle(const std::shared_ptr<sink>& sink)
                : ptr_(sink.get())
            {}
            attached_sink_handle(const attached_sink_handle&) = default;
            attached_sink_handle(attached_sink_handle&&) = default;

            bool operator == (const attached_sink_handle& other) const { return ptr_ == other.ptr_; }
            bool operator == (const std::shared_ptr<sink>& other) const { return ptr_ == other.get(); }

        private:
            const sink* ptr_; // do not derefence
        };

		attached_sink_handle attach_sink(const std::shared_ptr<sink>& new_sink);

		template<class T, typename ...Args>
		attached_sink_handle attach_sink(Args&&... args)
		{
			return attach_sink(std::make_shared<T>(std::forward<Args>(args)...));
		}

		void detach_sink(attached_sink_handle handle);

	public:
		bool level_enabled(log_level level) const;
		void log(const log_entry& entry);

	private:
		uint_fast32_t enabled_levels_; // contains a bitmask of all levels that are enabled on at least one sink
		std::vector<std::shared_ptr<sink>> sinks_;

		void calculate_enabled_levels();
	};

}
