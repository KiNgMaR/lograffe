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

namespace lograffe
{

namespace detail
{

	class time_formatter
	{
	public:
		static std::string to_rfc3339(const std::chrono::system_clock::time_point& system_timestamp)
		{
			std::time_t unix_timestamp{ std::chrono::system_clock::to_time_t(system_timestamp) };

			unsigned int millis = std::chrono::duration_cast<std::chrono::milliseconds>(
				system_timestamp.time_since_epoch()).count() % 1000;

			std::stringstream ss;

#ifdef _WIN32
			std::tm tm;
			gmtime_s(&tm, &unix_timestamp);
#else
			std::tm tm;
			localtime_r(&unix_timestamp, &tm);
#endif

			ss << (tm.tm_year + 1900) << '-';
			pad2(ss, tm.tm_mon + 1) << '-';
			pad2(ss, tm.tm_mday);
			ss << 'T';
			pad2(ss, tm.tm_hour) << ':';
			pad2(ss, tm.tm_min) << ':';
			pad2(ss, tm.tm_sec) << '.';
			pad3(ss, millis);

#ifdef _WIN32
			ss << 'Z';
#else
			ss << (tm.__tm_gmtoff < 0 ? '-' : '+');
			// TODO: this is super unportable
			pad2(ss, tm.__tm_gmtoff / 3600) << ':';
			pad2(ss, tm.__tm_gmtoff % 3600);
#endif
			return ss.str();
		}

		/*static std::string to_syslog(const std::chrono::system_clock::time_point& timestamp)
		{

		}*/

	private:
		static std::stringstream& pad2(std::stringstream& ss, unsigned int n)
		{
			if (n < 10)
				ss << '0';
			ss << n;
			return ss;
		}

		static std::stringstream& pad3(std::stringstream& ss, unsigned int n)
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
