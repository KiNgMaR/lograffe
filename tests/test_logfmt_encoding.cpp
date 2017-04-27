//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http ://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/formatters/detail/logfmt_encoding_impl.hpp>
#include <iostream>

using namespace lograffe::formatters::detail;

#define REQUIRE_INOUT_STR(call, in, expected_out) \
	{ std::stringstream ss; logfmt_encoding::call(ss, in); REQUIRE(ss.str() == std::string(expected_out)); }

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
	REQUIRE_INOUT_STR(encode_value, "with\x03""strange\x1F""characters", "\"with\\x03strange\\x1Fcharacters\"");
}