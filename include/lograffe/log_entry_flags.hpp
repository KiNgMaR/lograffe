//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <cstdint>

namespace lograffe
{

	enum class log_entry_flags : uint_fast32_t
	{
		flush = (1 << 0),
		sync  = (1 << 1),
		// stuff = (1 << 3),
	};

	inline constexpr log_entry_flags operator | (log_entry_flags a, log_entry_flags b)
	{
		return static_cast<log_entry_flags>(
			static_cast<uint_fast32_t>(a) | static_cast<uint_fast32_t>(b));
	}

	inline constexpr log_entry_flags operator & (log_entry_flags a, log_entry_flags b)
	{
		return static_cast<log_entry_flags>(
			static_cast<uint_fast32_t>(a) & static_cast<uint_fast32_t>(b));
	}

}
