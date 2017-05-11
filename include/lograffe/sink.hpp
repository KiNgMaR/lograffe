//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/log_level.hpp>
#include <lograffe/log_entry.hpp>

namespace lograffe
{

	//
	// Common base class for sink implementations.
	//
	class sink
	{
	public:
		sink(const sink&) = delete;
		sink(sink&&) = default;

		bool level_enabled(log_level level) const noexcept
		{
			return (level >= min_level_);
		}

		log_level min_level() const noexcept
		{
			return min_level_;
		}

		virtual void push(const log_entry& entry) = 0;

		virtual ~sink()
		{}

	protected:
		sink(log_level min_level)
			: min_level_(min_level)
		{}

	private:
		log_level min_level_;
	};

}
