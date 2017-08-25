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
	template<class Writer, class Formatter, class Mutex = std::mutex>
	class direct_sink : public sink
	{
	public:
		static_assert(std::is_base_of<writer, Writer>::value, "Writer must be derived from writer."); 
		static_assert(std::is_base_of<formatter, Formatter>::value, "Formatter must be derived from formatter.");

		direct_sink(log_level min_level, Writer&& writer, Formatter&& formatter = Formatter())
			: sink(min_level)
			, writer_(std::move(writer))
			, formatter_(std::move(formatter))
			, mutex_()
		{}

		void push(const log_entry& entry) override
		{
            const auto& formatted = formatter_.format_entry(entry);

			std::lock_guard<Mutex> lock(mutex_);

			writer_.write_line(formatted);
		}

	private:
		Writer writer_;
		Formatter formatter_;
		Mutex mutex_;
	};

}

}
