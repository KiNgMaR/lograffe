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

namespace lograffe
{

namespace sinks
{

	// This class implements a sink that doesn't add any functionality,
	// it simply passes entries synchronously through Formatter and Writer.
	template<class Formatter, class Writer, class Mutex = std::mutex>
	class direct_sink : public sink
	{
	public:
		static_assert(std::is_base_of<formatter, Formatter>::value, "Formatter must be derived from formatter.");
		static_assert(std::is_base_of<writer, Writer>::value, "Writer must be derived from writer.");

		direct_sink(log_level min_level, Formatter&& formatter, Writer&& writer)
			: sink(min_level)
			, formatter_(std::move(formatter))
			, writer_(std::move(writer))
			, mutex_()
		{}

		void push(const log_entry& entry) override
		{
			std::lock_guard<Mutex> lock(mutex_);

			writer_.write_line(formatter_.format_entry(entry));
		}

	private:
		Formatter formatter_;
		Writer writer_;
		Mutex mutex_;
	};

}

}
