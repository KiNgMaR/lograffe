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

		// All values are converted to strings immediately upon construction
		// of a field instance. However, for optimized processing in the
		// formatters it's good to know the origin type.
		enum class value_type
		{
			STRING,
			NUMBER_INTEGER,
			NUMBER_FRACTIONAL,
			BOOLEAN,
		};

		// various convenience constructors for different types of values:

		//
		// Warning: the current implementation will likely be replaced by something
		// more simple, more correct and equally performant.
		//

		template<class T>
		field(T&& name, bool value) noexcept
			: name_(std::forward<T>(name))
			, value_type_(value_type::BOOLEAN)
			, value_(value ? "true" : "false")
		{}

		template<class T>
		field(T&& name, const char* value) noexcept
			: name_(std::forward<T>(name))
			, value_type_(value_type::STRING)
			, value_(value)
		{}

		// for characters (this is probably wrong in some cases):
		template<class T>
		field(T&& name, char value) noexcept
			: name_(std::forward<T>(name))
			, value_type_(value_type::BOOLEAN)
			, value_(1, value)
		{}

		// for integer numbers:
		template<class TName, class TValue, typename std::enable_if<std::is_integral<TValue>::value, int>::type = 0>
		field(TName&& name, TValue value) noexcept
			: name_(std::forward<TName>(name))
			, value_type_(value_type::NUMBER_INTEGER)
			, value_{ std::to_string(value) }
		{}

		// for double numbers:
		template<class T>
		field(T&& name, double value) noexcept
			: name_(std::forward<T>(name))
			, value_type_(value_type::NUMBER_FRACTIONAL)
			, value_{ std::to_string(value) } // TODO: to be improved
		{}
		
		value_type get_value_type() const { return value_type_; }
		const std::string& name_ref() const { return name_;  }
		const std::string& value_ref() const { return value_; }

	private:
		const std::string name_;
		const value_type value_type_;
		const std::string value_;
	};

}
