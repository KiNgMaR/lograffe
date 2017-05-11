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

	template<class Stream>
	class ostream_writer_owning : public writer
	{
	public:
		template<typename... StreamConstructorArgs>
		ostream_writer_owning(StreamConstructorArgs... args)
			: stream_(args...)
		{}

		void write_line(const std::string& line) override
		{
			stream_ << line << std::endl;
		}

	protected:
		Stream stream_;
	};

}

}
