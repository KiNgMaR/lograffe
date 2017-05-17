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
#include <queue>

namespace lograffe
{

	// This class implements a sink that flushes log entries to the writer in batches
	// or on request (using the log_entry_flags::flush bit).
	template<class Writer, class Formatter, class Mutex = std::mutex>
	class buffered_sink : public sink
	{
	public:
		static_assert(std::is_base_of<writer, Writer>::value, "Writer must be derived from writer."); 
		static_assert(std::is_base_of<formatter, Formatter>::value, "Formatter must be derived from formatter.");

		buffered_sink(log_level min_level, Writer&& writer, Formatter&& formatter = Formatter(), size_t max_buffer_length = 10u)
			: sink(min_level)
			, writer_(std::move(writer))
			, formatter_(std::move(formatter))
			, mutex_()
			, buffer_()
			, max_buffer_length_(max_buffer_length)
		{}

		void push(const log_entry& entry) override
		{
			std::lock_guard<Mutex> lock(mutex_);

			buffer_.push(entry);

			if (entry.has_flag(log_entry_flags::flush) || buffer_.size() >= max_buffer_length_)
			{
				flush();
			}
		}

	private:
		void flush()
		{
			while (!queue_.empty())
			{
				writer_->write_line(formatter_->format_entry(queue_.pop()));
			}

			writer_->flush();
		}

	private:
		Writer writer_;
		Formatter formatter_;
		Mutex mutex_;
		std::queue<log_entry> buffer_;
		size_t max_buffer_length_;
	};

}
