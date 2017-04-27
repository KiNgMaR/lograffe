//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <string>
#include <sstream>

namespace lograffe
{

namespace formatters
{

namespace detail
{

	// Simplistic logfmt encoder. Does not care about the character set.
	class logfmt_encoding
	{
	public:
		static inline void encode_key(std::stringstream& ss, const std::string& key)
		{
			if (key.empty() || contains_blacklisted_character(key))
			{
				ss << "(invalid_key)";
			}
			else
			{
				ss << key;
			}
		}

		static inline void encode_value(std::stringstream& ss, const std::string& value)
		{
			if (!contains_blacklisted_character(value))
			{
				ss << value;

				return;
			}

			ss << '"';

			for (const char c : value)
			{
				if (c == '\n')
					ss << "\\n";
				else if (c == '\r')
					ss << "\\r";
				else if (c == '\t')
					ss << "\\t";
				else if (c < 0x20)
				{
					ss << "\\x";
					ss << HEXALPHA[static_cast<unsigned char>(c) >> 4];
					ss << HEXALPHA[static_cast<unsigned char>(c) & 15];
				}
				else if (c == '\\' || c == '"')
					ss << '\\' << c;
				else
					ss << c;
			}

			ss << '"';
		}

	private:
		static inline bool contains_blacklisted_character(const std::string& str)
		{
			// stupid stuff because searching for \x00 with find_first_of requires an std::string instance.
			for (const char c : str)
			{
				if (c <= 0x20 || c == '"' || c == '=')
					return true;
			}

			return false;
		}

		constexpr static const char* HEXALPHA = "0123456789ABCDEF";
	};

}

}

}
