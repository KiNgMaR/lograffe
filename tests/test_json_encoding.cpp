//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http ://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/formatters/detail/json_encoding.hpp>
#include <sstream>

using namespace lograffe::formatters::detail;

#define REQUIRE_INOUT_ESCAPED(key, value, expected_out) \
	{ std::stringstream ss; json_encoding::encode_pair(ss, key, value, true, false); REQUIRE(ss.str() == std::string(expected_out)); }

#define REQUIRE_INOUT_UNESCAPED(key, value, expected_out) \
	{ std::stringstream ss; json_encoding::encode_pair(ss, key, value, false, false); REQUIRE(ss.str() == std::string(expected_out)); }

TEST_CASE("json_encoding: Basics", "[json_encoding]")
{
    REQUIRE_INOUT_ESCAPED("time", "2018-01-01T12:34:56", R"("time":"2018-01-01T12:34:56")");
    REQUIRE_INOUT_ESCAPED("msg", "new\r\nline", R"("msg":"new\r\nline")");
    REQUIRE_INOUT_ESCAPED("msg", "with\x03""strange\x1F""characters", R"("msg":"with\u0003strange\u001fcharacters")");
    REQUIRE_INOUT_ESCAPED("key with\x03""strange\x1F""characters", "", R"("key with\u0003strange\u001fcharacters":"")");
}

TEST_CASE("json_encoding: UTF-8 and invalid UTF-8 must be handled correctly", "[json_encoding]")
{
    REQUIRE_INOUT_ESCAPED("msg", "V\xc3\xa4lid UTF-8", "\"msg\":\"V\\u00e4lid UTF-8\"");
    REQUIRE_INOUT_ESCAPED("msg", "\xd0\xaf", "\"msg\":\"\\u042f\"");
    REQUIRE_INOUT_ESCAPED("msg", "Invalid \xDCTF-8", "\"msg\":\"Invalid \\ufffdTF-8\"");
}

TEST_CASE("json_encoding: unescaped flag", "[json_encoding]")
{
    REQUIRE_INOUT_UNESCAPED("success", "false", R"("success":false)");
    REQUIRE_INOUT_UNESCAPED("count", "1337", R"("count":1337)");
}
