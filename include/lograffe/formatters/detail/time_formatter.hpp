//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <cstdint>

namespace lograffe
{

namespace formatters
{

namespace detail
{

	class time_formatter
	{
	public:
		static std::string to_rfc3339(const std::chrono::system_clock::time_point& system_timestamp)
		{
			std::time_t unix_timestamp{ std::chrono::system_clock::to_time_t(system_timestamp) };

			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
				system_timestamp.time_since_epoch()).count() % 1000;

			std::stringstream ss;
			std::tm tm;

#ifdef _WIN32
			gmtime_s(&tm, &unix_timestamp);
#else
			gmtime_r(&unix_timestamp, &tm);
#endif

			ss << (tm.tm_year + 1900) << '-';
			pad2(ss, tm.tm_mon + 1) << '-';
			pad2(ss, tm.tm_mday);
			ss << 'T';
			pad2(ss, tm.tm_hour) << ':';
			pad2(ss, tm.tm_min) << ':';
			pad2(ss, tm.tm_sec) << '.';
			pad3(ss, millis);

			ss << 'Z';
#if 0
			int offset = gmtoff(tm.tm_isdst);
			ss << (offset < 0 ? '-' : '+');
			pad2(ss, abs(offset / 60)) << ':';
			pad2(ss, abs(offset % 60));
#endif
			return ss.str();
		}

		/*static std::string to_syslog(const std::chrono::system_clock::time_point& timestamp)
		{

		}*/

	private:
		static std::stringstream& pad2(std::stringstream& ss, uint64_t n)
		{
			if (n < 10)
				ss << '0';
			ss << n;
			return ss;
		}

		static std::stringstream& pad3(std::stringstream& ss, uint64_t n)
		{
			if (n < 10)
				ss << '0';
			if (n < 100)
				ss << '0';
			ss << n;
			return ss;
		}

	};

}

}

}
