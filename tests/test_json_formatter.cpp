//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http ://www.boost.org/LICENSE_1_0.txt)
//

#include "catch.hpp"
#include <lograffe/formatters/json_formatter.hpp>
#include <lograffe/logger.hpp>
#include <regex>

using namespace lograffe;

TEST_CASE("json_formatter: basics", "[json_formatter]")
{
    logger dummy_logger;
    log_entry my_log_entry(dummy_logger, log_level::info, "info");

    my_log_entry << "Hello World!";
    my_log_entry << field("bool_field", false);
    my_log_entry << field("float_field", 3.14159);
    my_log_entry << field("int_field", 31337);

    const std::string output = formatters::json_formatter().format_entry(my_log_entry);

    // this is pretty stupid, should come up with a better way to test:
    REQUIRE_THAT(output, Catch::Matchers::Matches(R"(^\{"time":".*?","level":"info","msg":"Hello World!","bool_field":false,"float_field":3\.141590,"int_field":31337\}$)"));
}
