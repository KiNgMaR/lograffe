//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http ://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/formatters/detail/logfmt_encoding.hpp>
#include <sstream>

using namespace lograffe::formatters::detail;

#define REQUIRE_INOUT_STR(call, in, expected_out) \
	{ std::stringstream ss; logfmt_encoding::call(ss, in); REQUIRE(ss.str() == std::string(expected_out)); }

#define REQUIRE_INOUT_PAIR(key, value, expected_out) \
	{ std::stringstream ss; logfmt_encoding::encode_pair(ss, key, value, true); REQUIRE(ss.str() == std::string(expected_out)); }

TEST_CASE("Invalid keys should be replaced", "[logfmt_encoding]")
{
	REQUIRE_INOUT_STR(encode_key, "", "(invalid_key)");
	REQUIRE_INOUT_STR(encode_key, "with space", "(invalid_key)");
	REQUIRE_INOUT_STR(encode_key, "newline\r\n", "(invalid_key)");
	REQUIRE_INOUT_STR(encode_key, "weird\x03""char", "(invalid_key)");
	REQUIRE_INOUT_STR(encode_key, "Cool_Key", "Cool_Key");
	REQUIRE_INOUT_STR(encode_key, "123", "123");
}

TEST_CASE("Values should be quoted when necessary", "[logfmt_encoding]")
{
	REQUIRE_INOUT_STR(encode_value, "", "");
	REQUIRE_INOUT_STR(encode_value, "with space", "\"with space\"");
	REQUIRE_INOUT_STR(encode_value, "WITHOUT_space", "WITHOUT_space");
	REQUIRE_INOUT_STR(encode_value, "123", "123");
	REQUIRE_INOUT_STR(encode_value, "(HeLLoW)", "(HeLLoW)");
	REQUIRE_INOUT_STR(encode_value, "\\", "\\");
	REQUIRE_INOUT_STR(encode_value, " ", "\" \"");
	REQUIRE_INOUT_STR(encode_value, "=\\", R"("=\\")");
	REQUIRE_INOUT_STR(encode_value, "\\\"", "\"" "\\" "\\" "\\" "\"\"");
	REQUIRE_INOUT_STR(encode_value, "2008-09-08T22:47:31+07:00", "2008-09-08T22:47:31+07:00");
	REQUIRE_INOUT_STR(encode_value, "with\rnew\nline", "\"with\\rnew\\nline\"");
	REQUIRE_INOUT_STR(encode_value, "with\x03""strange\x1F""characters", "\"with\\u0003strange\\u001fcharacters\"");
}

TEST_CASE("UTF-8 handling should be in place", "[logfmt_encoding]")
{
    REQUIRE_INOUT_STR(encode_value, "V\xc3\xa4lid UTF-8", "\"V\\u00e4lid UTF-8\"");
    REQUIRE_INOUT_STR(encode_value, "\xd0\xaf", "\"\\u042f\"");
    REQUIRE_INOUT_STR(encode_value, "Invalid \xDCTF-8", "\"Invalid \\ufffdTF-8\"");
}

TEST_CASE("Helper method for pairs should work as expected", "[logfmt_encoding]")
{
	REQUIRE_INOUT_PAIR("my key", "my value", " (invalid_key)=\"my value\"");
	REQUIRE_INOUT_PAIR("my_key", "coolVal", " my_key=coolVal");
}
