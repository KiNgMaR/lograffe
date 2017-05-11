//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/formatter.hpp>
#include <lograffe/formatters/detail/logfmt_encoding_impl.hpp>
#include <lograffe/formatters/detail/time_formatter_impl.hpp>
#include <string>

namespace lograffe
{

namespace formatters
{

	class logfmt_formatter : public formatter
	{
	public:
		logfmt_formatter()
			: formatter()
		{}

		virtual std::string format_entry(const log_entry& entry) override
		{
			std::stringstream ss;

			// TODO: move field names out of invididual formatter
			ss << "time=" << detail::time_formatter::to_rfc3339(entry.timestamp_ref());

			if (entry.message_ref().rdbuf()->in_avail() != 0)
			{
				// TODO: move field names out of invididual formatter
				ss << " msg=";
				detail::logfmt_encoding::encode_value(ss, entry.message_ref().str());
			}

			entry.fields_ref().for_each([&ss](const field& field)
			{
				ss << ' ';
				detail::logfmt_encoding::encode_key(ss, field.name_ref());
				ss << '=';
				detail::logfmt_encoding::encode_value(ss, field.value_ref());
			});

			return ss.str();
		}
	};

}

}
