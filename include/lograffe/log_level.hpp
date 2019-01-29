//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <cstdint>
#include <type_traits>

namespace lograffe
{

#ifndef LOGRAFFE_CUSTOM_LEVELS

	// lograffe default log levels, from debug to fatal.
	enum class log_level : uint_fast32_t
	{
		debug = (1 << 5) - 1,
		info  = (1 << 4) - 1,
		warn  = (1 << 3) - 1,
		error = (1 << 2) - 1,
		fatal = (1 << 1) - 1,
	};

#else

	using log_level = LOGRAFFE_CUSTOM_LEVELS;

#endif // LOGRAFFE_CUSTOM_LEVELS

	static_assert(std::is_enum<log_level>::value, "custom log level has to be an enum");
	static_assert(std::is_convertible<std::underlying_type<log_level>::type, uint_fast32_t>::value,
		"custom log level type should be convertible to a uint_fast32_t");

}
