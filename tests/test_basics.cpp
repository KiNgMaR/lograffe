//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http ://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/lograffe.hpp>
#include <lograffe/sinks/ostream_sink.hpp>
#include <lograffe/formatters/logfmt_formatter.hpp>
#include <lograffe/alias.hpp>
#include <sstream>

TEST_CASE("Logging with fields should work", "[basics]")
{
	lograffe::logger lgr;

	lograffe::log_entry(lgr, lograffe::log_level::warn, "warn")
		<< logr::field("a", true)
		<< logr::field{ "a2", 623932928349023423ull }
		<< logr::fields{
			{ "b", false },
			{ "c", 7 }
		}
		<< "hello"
		<< std::string("world");

	logr::fields copy_me{ { "x", false }, { "y", 12.52 } };

	lograffe::log_entry(lgr, lograffe::log_level::warn, "warn")
		<< copy_me;

	lograffe::log_entry(lgr, lograffe::log_level::warn, "warn")
		<< copy_me;

	lograffe::log_entry(lgr, lograffe::log_level::info, "info")
		<< 5ul
		<< std::string("test");

	//lograffe::detail::log_entry(lgr, lograffe::log_level::info)
}

TEST_CASE("Logging to a stringstream should work", "[basics]")
{
	std::stringstream ss;

	lograffe::logger lgr;
	//lgr.attach_sink(std::make_unique<lograffe::sinks::ostream_sink>(std::make_unique<lograffe::formatters::logfmt_formatter>(), ss));
	lgr.attach_sink<lograffe::sinks::ostream_sink, lograffe::formatters::logfmt_formatter>(logr::log_level::warn, ss);

	lograffe::log_entry(lgr, lograffe::log_level::warn, "warn")
		<< logr::field("a", true)
		<< logr::field{ "a2", 623932928349023423ull }
		<< logr::field("dangerous", "Very Dangerous \" string!")
		<< logr::fields{
			{ "b", false },
			{ "c", 7 }
		}
		<< "hello"
		<< ' '
		<< std::string("world");

	std::string result = ss.str();
	std::cout << "[" << result << "]" << std::endl;
}
