//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/sink.hpp>
#include <lograffe/formatter.hpp>
#include <iostream>

namespace lograffe
{

namespace sinks
{

	// This sink can be used to log to any std::ostream. The sink only keeps
	// a reference to the actual ostream used, so you have to make sure that
	// it does not go out of scope.
	class ostream_sink : public sink
	{
	public:
		ostream_sink(log_level min_level, std::unique_ptr<formatter>&& fmter, std::ostream& stream)
			: sink(min_level, std::move(fmter))
			, stream_(stream)
		{}

		ostream_sink(const ostream_sink&) = delete;
		ostream_sink(ostream_sink&&) = default;

		ostream_sink operator = (const ostream_sink&) = delete;
		ostream_sink operator = (ostream_sink&&) = delete;
			
	protected:
		std::ostream& stream_;

		void push_line(std::string&& line) override
		{
			stream_ << line;
		}
	};

}

}
