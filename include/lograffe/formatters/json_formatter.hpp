//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/formatter.hpp>
#include <lograffe/formatters/detail/json_encoding.hpp>
#include <lograffe/formatters/detail/time_formatter.hpp>
#include <string>

namespace lograffe
{

	namespace formatters
	{

		class json_formatter : public formatter
		{
		public:
            json_formatter()
                : formatter()
                , field_name_timestamp_("time")
                , field_name_level_("level")
                , field_name_message_("msg")
            {}

            std::string format_entry(const log_entry& entry) override
            {
                std::stringstream ss;

                ss << '{';

                detail::json_encoding::encode_pair(ss, field_name_timestamp_, detail::time_formatter::to_rfc3339(entry.timestamp_ref()), true, false);
                detail::json_encoding::encode_pair(ss, field_name_level_, entry.level_name());

                if (entry.message_ref().rdbuf()->in_avail() != 0)
                {
                    detail::json_encoding::encode_pair(ss, field_name_message_, entry.message_ref().str());
                }

                entry.fields_ref().for_each([&ss](const field& field)
                {
                    detail::json_encoding::encode_pair(ss, field.name_ref(), field.value_ref(), field.get_value_type() == field::value_type::STRING);
                });

                ss << '}';

                return ss.str();
            }

        private:
            const char* field_name_timestamp_;
            const char* field_name_level_;
            const char* field_name_message_;
		};

	}

}
