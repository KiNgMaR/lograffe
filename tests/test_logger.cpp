//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/lograffe.hpp>
#include <lograffe/sinks/null_sink.hpp>

TEST_CASE("Higher log levels should include/enable lower ones", "[logger]")
{
	lograffe::logger lgr;

	lgr.attach_sink<lograffe::sinks::null_sink>(lograffe::log_level::warn);

	REQUIRE(lgr.level_enabled(lograffe::log_level::warn));
	REQUIRE(lgr.level_enabled(lograffe::log_level::error));
	REQUIRE(lgr.level_enabled(lograffe::log_level::fatal));

	REQUIRE_FALSE(lgr.level_enabled(lograffe::log_level::info));
	REQUIRE_FALSE(lgr.level_enabled(lograffe::log_level::debug));
}

TEST_CASE("The lowest level from multiple sinks should apply", "[logger]")
{
    lograffe::logger lgr;

    lgr.attach_sink<lograffe::sinks::null_sink>(lograffe::log_level::error);
    lgr.attach_sink<lograffe::sinks::null_sink>(lograffe::log_level::fatal);

    REQUIRE(lgr.level_enabled(lograffe::log_level::error));
    REQUIRE(lgr.level_enabled(lograffe::log_level::fatal));

    REQUIRE_FALSE(lgr.level_enabled(lograffe::log_level::warn));
    REQUIRE_FALSE(lgr.level_enabled(lograffe::log_level::info));
    REQUIRE_FALSE(lgr.level_enabled(lograffe::log_level::debug));
}
