//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#define LOG(LEVEL) \
	if (lograffe::logger::current()->level_enabled(lograffe::log_level::LEVEL)) \
		lograffe::detail::log_entry(lograffe::logger::current(), lograffe::log_level::LEVEL, #LEVEL)

#define LOG_IF(BOOLEAN_EXPR, LEVEL) \
	if (BOOLEAN_EXPR) LOG(LEVEL)
