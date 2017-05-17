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
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>

namespace lograffe
{

	// This class implements a sink that uses a background thread for
	// formatting and writing. The background thread must be started
	// and managed by the owning process and invoke the run_writer()
	// method. Log entries with the log_entry_flags::sync bit set
	// will cause the calling thread to wait for the flush to complete.
	template<class Writer, class Formatter>
	class async_sink : public sink
	{
	public:
		static_assert(std::is_base_of<writer, Writer>::value, "Writer must be derived from writer."); 
		static_assert(std::is_base_of<formatter, Formatter>::value, "Formatter must be derived from formatter.");

		async_sink(log_level min_level, Writer&& writer, Formatter&& formatter = Formatter(), std::chrono::seconds flush_interval = 5, size_t max_buffer_length = 0u)
			: sink(min_level)
			, writer_(std::move(writer))
			, formatter_(std::move(formatter))
			, buffer_()
			, buffer_mutex_()
			, writer_mutex_(),
			, max_buffer_length_(max_buffer_length)
			, flush_interval_(flush_interval < 1 ? 1 : flush_interval)
			, flush_notifier_()
			, stopped_()
		{}

		void push(const log_entry& entry) override
		{
			if (entry.has_flag(log_entry_flags::sync)) // immediately sync to disk (from this thread for simplicity)
			{
				std::unique_lock<std::mutex> lock_buffer(buffer_mutex_, std::defer_lock);
				std::unique_lock<std::mutex> lock_writer(writer_mutex_, std::defer_lock);

				std::lock(lock_mutex, lock_writer);

				while (!buffer_.empty())
				{
					writer_.write_line(formatter_.format_entry(buffer_.pop()));
				}

				writer_.write_line(formatter_.format_entry(entry));
			}
			else
			{
				std::unique_lock<std::mutex> lock(buffer_mutex_);

				buffer_.push(entry);

				if (entry.has_flag(log_entry_flags::flush) || buffer_.size() >= max_buffer_length_) // ask writer thread to flush
				{
					flush_notifier_.notify_all();
				}
			}
		}

		void run_writer()
		{
			std::queue<log_entry> entries_to_be_written;

			while (!stopped_)
			{
				// move to local stack to avoid blocking buffer_mutex_ during the write operation:
				{
					std::unique_lock<std::mutex> lock(buffer_mutex_);

					flush_notifier_.wait_for(flush_interval_);

					std::swap(entries_to_be_written, buffer_);
				}

				// flush to the writer:
				{
					std::lock_guard<std::mutex> lock(writer_mutex_);

					while (!entries_to_be_written.empty())
					{
						writer_.write_line(formatter_.format_entry(entries_to_be_written.pop()));
					}
				}
			}
		}

	private:
		Writer writer_;
		Formatter formatter_;
		std::queue<log_entry> buffer_;
		std::mutex buffer_mutex_;
		std::mutex writer_mutex_;
		size_t max_buffer_length_;
		std::chrono::seconds flush_interval_;
		std::condition_variable flush_notifier_;
		bool stopped_;
	};

}
