//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/sink.hpp>
#include <lograffe/formatter.hpp>
#include <lograffe/writer.hpp>
#include <type_traits>
#include <thread>
#include <chrono>
#include <queue>

namespace lograffe
{

	// This class implements a sink that uses a background thread for
	// formatting and writing. The background thread must be started
	// and managed by the owning process and invoke the run_writer()
	// method. Log entries with the log_entry_flags::sync bit set
	// will cause the calling thread to wait for the flush to complete.
	template<class Formatter, class Writer, class Mutex = std::mutex>
	class async_sink : public sink
	{
	public:
		static_assert(std::is_base_of<formatter, Formatter>::value, "Formatter must be derived from formatter.");
		static_assert(std::is_base_of<writer, Writer>::value, "Writer must be derived from writer.");

		async_sink(log_level min_level, Formatter&& formatter, Writer&& writer, std::chrono::seconds flush_interval = 1, size_t max_buffer_length = 0u)
			: sink(min_level)
			, formatter_(std::move(formatter))
			, writer_(std::move(writer))
			, mutex_()
			, max_buffer_length_(max_buffer_length)
			, pending_syncs_(0)
		{}

		void push(const log_entry& entry) override
		{
			std::lock_guard<Mutex> lock(mutex_);

			buffer_.push(entry);

			if (entry.has_flag(log_entry_flags::flush) || buffer_.size() >= max_buffer_length_)
			{
				flush();
			}

			//writer_->write_line(formatter_->format_entry(entry));
		}

		void run_writer()
		{

		}

	private:
		Formatter formatter_;
		Writer writer_;
		Mutex mutex_;
		std::chrono::seconds flush_interval_;
		std::queue<log_entry> buffer_;
		size_t max_buffer_length_;
		std::atomic<size_t> pending_syncs_;
	};

}
