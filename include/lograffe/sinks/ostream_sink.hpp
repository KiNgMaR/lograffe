//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/sink.hpp>
#include <iostream>

namespace lograffe
{

	namespace sinks
	{

		class ostream_sink : public sink
		{
		public:
			ostream_sink(std::ostream& stream)
				: sink()
				, stream_(stream)
			{}

			ostream_sink(const ostream_sink&) = delete;
			ostream_sink(ostream_sink&&) = default;

			ostream_sink operator = (const ostream_sink&) = delete;
			ostream_sink operator = (ostream_sink&&) = delete;
			
		protected:
			std::ostream& stream_;

			void push_line(const std::string& line)
			{
				stream_ << line;
			}

			void push_line(std::string&& line)
			{
				stream_ << line;
			}
		};

	}
	
}
