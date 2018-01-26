//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/formatters/detail/utf8_dfa.hpp>
#include <string>
#include <sstream>
#include <iomanip>

namespace lograffe
{

namespace formatters
{

namespace detail
{

    // Simplistic json encoder. Expects UTF-8 encoded strings and replaces invalid UTF-8 with a unicode substitution character.
    class json_encoding
    {
    public:
        static inline void encode_pair(std::stringstream& ss, const std::string& key, const std::string& value, bool quote_value = true, bool comma = true)
        {
            if (comma)
            {
                ss << ',';
            }

            encode_string(ss, key);

            ss << ':';

            if (quote_value)
            {
                encode_string(ss, value);
            }
            else
            {
                ss << value;
            }
        }

    private:
        static inline void encode_string(std::stringstream& ss, const std::string& str)
        {
            // remember stream flags to restore them later:
            std::ios ss_state(nullptr);
            ss_state.copyfmt(ss);

            ss << '"';
            ss << std::hex << std::setfill('0');

            // do the UTF-8 dance:
            auto prev = utf8_dfa::UTF8_ACCEPT;
            auto current = utf8_dfa::UTF8_ACCEPT;

            uint32_t codepoint = 0;

            for (size_t p = 0, length = str.length(); p < length; ++p)
            {
                prev = current;

                switch (utf8_dfa::decode(&current, &codepoint, static_cast<unsigned char>(str[p])))
                {
                case utf8_dfa::UTF8_ACCEPT:
                    // A properly encoded character has been found.
                    if (codepoint == '\n')
                    {
                        ss << "\\n";
                    }
                    else if (codepoint == '\r')
                    {
                        ss << "\\r";
                    }
                    else if (codepoint == '\t')
                    {
                        ss << "\\t";
                    }
                    else if (codepoint == '\\' || codepoint == '"')
                    {
                        ss << '\\' << static_cast<char>(codepoint);
                    }
                    else if (codepoint >= 0x20 && codepoint < 0x80)
                    {
                        ss << static_cast<char>(codepoint);
                    }
                    else
                    {
                        ss << "\\u" << std::setw(4) << codepoint;
                    }
                    break;

                case utf8_dfa::UTF8_REJECT:
                    // The byte is invalid, replace it and restart.
                    ss << "\\ufffd";

                    current = utf8_dfa::UTF8_ACCEPT;

                    if (prev != utf8_dfa::UTF8_ACCEPT)
                    {
                        --p;
                    }
                    break;
                }
            }

            // TODO: check final state

            ss << '"';

            ss.copyfmt(ss_state);
        }
    };

}

}

}
