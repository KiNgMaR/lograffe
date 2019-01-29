//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/lograffe.hpp>
#include <lograffe/sinks/null_sink.hpp>

TEST_CASE("On the sink, higher log levels should include/enable lower ones", "[sink]")
{
    lograffe::sinks::null_sink sink(lograffe::log_level::warn);

    REQUIRE(sink.level_enabled(lograffe::log_level::warn));
    REQUIRE(sink.level_enabled(lograffe::log_level::error));
    REQUIRE(sink.level_enabled(lograffe::log_level::fatal));

    REQUIRE_FALSE(sink.level_enabled(lograffe::log_level::info));
    REQUIRE_FALSE(sink.level_enabled(lograffe::log_level::debug));
}
