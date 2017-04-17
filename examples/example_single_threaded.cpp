//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http ://www.boost.org/LICENSE_1_0.txt)
//

// lograffe
#include <lograffe/lograffe.hpp>
#include <lograffe/alias.hpp> // alias lograffe namespace as logr
#include <lograffe/sinks/ostream_sink.hpp>
#include <lograffe/formatters/logfmt_formatter.hpp>

// stdlib
#include <string>
#include <vector>
#include <fstream>

// the ostream_sink keeps a reference to this, so it must not go out of scope!
std::ofstream output_file;

static void SetUpLogging()
{
	using namespace logr;

	output_file.open("example.log", std::ofstream::app);

	logger my_logger;

	// log
	// - all entries >= level info
	// - to a file ostream
	// - using the logfmt formatter.

	my_logger.attach_sink<sinks::ostream_sink, formatters::logfmt_formatter>(log_level::info, output_file);

	// pass ownership to static/thread local logger management:
	logger::set_current(std::move(my_logger));
}

int main(int, char **)
{
	LOG(info) << "Oops, this won't be be logged...";

	SetUpLogging();

	LOG(info) << "Logging ready!";

	std::vector<std::string> giraffes{ "gir", "affe" };

	LOG(info) << "A group of animals emerges from the savanna" << logr::fields{
		{ "animal", "giraffe" },
		{ "size", giraffes.size() }
	};

	LOG(debug) << logr::field{ "line", __LINE__ };

	return 0;
}
