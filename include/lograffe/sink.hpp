//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/log_level.hpp>
#include <lograffe/formatter.hpp>
#include <string>
#include <memory>

namespace lograffe
{

	class sink
	{
	public:
		sink(const sink&) = delete;
		sink(sink&&) = default;

		log_level min_level() const noexcept
		{
			return min_level_;
		}

		void push(const log_entry& entry)
		{
			if (entry.level() >= min_level_)
			{
				push_line(formatter_->format_entry(entry));
			}
		}

		virtual ~sink()
		{}

	protected:
		sink(log_level min_level, std::unique_ptr<formatter>&& fmter)
			: min_level_(min_level)
			, formatter_(std::move(fmter))
		{}

		//virtual void push_line(const std::string& line) = 0;
		virtual void push_line(std::string&& line) = 0;

	private:
		std::unique_ptr<formatter> formatter_;
		log_level min_level_;
	};

}
