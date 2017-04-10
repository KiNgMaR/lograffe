//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/field.hpp>

TEST_CASE("construction from bool (with const char* name)", "[field]")
{
	lograffe::field fbt("bool_field", true);
	lograffe::field fbti{ "bool_field", true };

	CHECK(fbt.name_ref() == "bool_field");
	CHECK(fbt.value_ref() == "true");
	CHECK(fbti.value_ref() == "true");

	lograffe::field fbf("bool_field", false);
	lograffe::field fbfi{ "bool_field", false };

	CHECK(fbf.value_ref() == "false");
	CHECK(fbfi.value_ref() == "false");
	CHECK(fbfi.name_ref() == "bool_field");
}

TEST_CASE("construction from bool (with const std::string name)", "[field]")
{
	const std::string field_name = "bool_field";

	lograffe::field fbt(field_name, true);
	lograffe::field fbfi{ field_name, false };

	CHECK(fbt.value_ref() == "true");
	CHECK(fbfi.value_ref() == "false");

	CHECK(fbt.name_ref() == "bool_field");
	CHECK(fbfi.name_ref() == "bool_field");
}

TEST_CASE("construction from bool (with std::string&& name)", "[field]")
{
	lograffe::field fbt(std::move(std::string("bool_field")), true);
	lograffe::field fbfi{ std::move(std::string("bool_field")), false };

	CHECK(fbt.value_ref() == "true");
	CHECK(fbfi.value_ref() == "false");

	CHECK(fbt.name_ref() == "bool_field");
	CHECK(fbfi.name_ref() == "bool_field");
}
