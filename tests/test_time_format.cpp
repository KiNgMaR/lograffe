//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http ://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/detail/time_format.hpp>
#include <regex>
#include <iostream>

using namespace lograffe::detail;

TEST_CASE("RFC3339 format should match", "[time_formatter]")
{
	const std::string result = time_format::to_rfc3339(std::chrono::system_clock::now());

	REQUIRE(std::regex_match(result, std::regex(R"(^20\d\d-(0\d|1[012])-[0123]\dT[0-5]\d:[0-5]\d:[0-5]\d\.\d{3}(Z|[+-][0-5]\d:[0-5])$)")));
}
