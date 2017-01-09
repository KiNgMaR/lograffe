//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/log_level.hpp>
#include <string>

namespace lograffe
{

	class sink
	{
	public:
		sink(const sink&) = delete;
		sink(sink&&) = default;
		
		void min_level(log_level level) noexcept
		{
			m_min_level = level;
		}

		log_level min_level() const noexcept
		{
			return m_min_level;
		}

		template<class T>
		void push(log_level level, T&& line)
		{
			if (level >= m_min_level)
			{
				push_line(std::forward<T>(line));
			}
		}

		virtual ~sink()
		{}

	protected:
		sink()
			: m_min_level()
		{}

		virtual void push_line(const std::string& line) = 0;
		virtual void push_line(std::string&& line) = 0;

	private:
		log_level m_min_level;
	};

}
