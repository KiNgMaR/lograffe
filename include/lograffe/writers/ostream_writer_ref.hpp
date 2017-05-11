//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/writer.hpp>
#include <string>

namespace lograffe
{

namespace writers
{

	class ostream_writer_ref : public writer
	{
	public:
		ostream_writer_ref(std::ostream& stream)
			: stream_(stream)
		{}

		void write_line(const std::string& line) override
		{
			stream_ << line << std::endl;
		}

	protected:
		std::ostream& stream_;
	};

}

}
