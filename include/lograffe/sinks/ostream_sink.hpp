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
			// takes ownership of the given stream
			template<class T, typename std::enable_if<std::is_base_of<std::ostream, std::decay<T>::type>::value, int>::type = 0>
			ostream_sink(T&& stream)
				: sink()
				, m_stream(std::move(stream))
			{}

			ostream_sink(const ostream_sink&) = delete;
			ostream_sink(ostream_sink&&) = default;

			ostream_sink operator = (const ostream_sink&) = delete;
			ostream_sink operator = (ostream_sink&&) = delete;
			
		protected:
			std::ostream m_stream;

			void push_line(const std::string& line)
			{
				m_stream << line;
			}

			void push_line(std::string&& line)
			{
				m_stream << line;
			}
		};

	}
	
}
