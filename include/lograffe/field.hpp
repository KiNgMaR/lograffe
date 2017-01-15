//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <string>

namespace lograffe
{

	class field
	{
	public:
		field() = delete;
		field(const field&) = default;
		field(field&&) = default;

		// delete assignment operators until we need them:
		field& operator = (const field&) = delete;
		field& operator = (field&&) = delete;

		// various convenience constructors for different types of values:

		// Warning: the current implementation will likely be replaced by something
		// more simple and equally performant.

		template<class T>
		field(T&& name, bool value) noexcept
			: name_(std::forward<T>(name))
			, value_(value ? "true" : "false")
		{}
		
		// for characters (this is probably wrong in some cases):
		template<class T>
		field(T&& name, char value) noexcept
			: name_(std::forward<T>(name))
			, value_(1, value)
		{}

		// for integer numbers:
		template<class TName, class TValue, typename std::enable_if<std::is_integral<TValue>::value, int>::type = 0>
		field(TName&& name, TValue value) noexcept
			: name_(std::forward<TName>(name))
			, value_{ std::to_string(value) }
		{}

		// for double numbers:
		template<class T>
		field(T&& name, double value) noexcept
			: name_(std::forward<T>(name))
			, value_{ std::to_string(value) } // TODO: to be improved
		{}
		
	private:
		const std::string name_;
		const std::string value_;
	};

}
