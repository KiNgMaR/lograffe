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

	// This sink can be used to log to any std::ostream-like class. The sink
	// takes ownership of the stream instance.
	template<class T>
	class owning_ostream_sink : public sink
	{
	public:
		template<typename... TConstructorArgs>
		owning_ostream_sink(log_level min_level, std::unique_ptr<formatter>&& fmter, TConstructorArgs... args)
			: sink(min_level, std::move(fmter))
			, stream_(args...)
		{}

		owning_ostream_sink(const owning_ostream_sink<T>&) = delete;
		owning_ostream_sink(owning_ostream_sink<T>&&) = default;

		owning_ostream_sink operator = (const owning_ostream_sink<T>&) = delete;
		owning_ostream_sink operator = (owning_ostream_sink<T>&&) = delete;

	protected:
		T stream_;

		void push_line(std::string&& line) override
		{
			stream_ << line;
		}
	};

}

}
