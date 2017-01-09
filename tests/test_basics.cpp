//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http ://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/lograffe.hpp>
#include <lograffe/alias.hpp>

TEST_CASE("Logging with fields should work", "[basics]")
{
	lograffe::logger lgr;

	lograffe::log_entry(lgr, lograffe::log_level::warn)
		<< logr::field("a", true)
		<< logr::field{ "a2", 623932928349023423ull }
		<< logr::fields{
			{ "b", false },
			{ "c", 7 }
		}
		<< "hello"
		<< std::string("world");

	logr::fields copy_me{ { "x", false }, { "y", 12.52 } };

	lograffe::log_entry(lgr, lograffe::log_level::warn)
		<< copy_me;

	lograffe::log_entry(lgr, lograffe::log_level::warn)
		<< copy_me;

	lograffe::log_entry(lgr, lograffe::log_level::info)
		<< 5ul
		<< std::string("test");

	//lograffe::detail::log_entry(lgr, lograffe::log_level::info)
}
