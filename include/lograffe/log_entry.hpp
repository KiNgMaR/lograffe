//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/field.hpp>
#include <lograffe/fields.hpp>
#include <lograffe/log_level.hpp>
#include <sstream>

namespace lograffe
{
	class logger;

	class log_entry
	{
	public:
		log_entry(logger& logger_instance, log_level level)
			: logger_instance_(logger_instance)
			, level_(level)
			, entry_fields_{}
		{}
			
		log_entry() = delete;

		log_entry& operator << (lograffe::fields&& new_fields)
		{
			entry_fields_.append(std::move(new_fields));

			return *this;
		}

		log_entry& operator << (const lograffe::fields& new_fields)
		{
			entry_fields_.append(new_fields);

			return *this;
		}

		log_entry& operator << (lograffe::field&& new_field)
		{
			entry_fields_.append(std::move(new_field));

			return *this;
		}

		log_entry& operator << (const lograffe::field& new_field)
		{
			entry_fields_.append(new_field);

			return *this;
		}

		// Shift operator enabled for all types that "work" on stringstream's operator <<. This
		// is used to append things to the "message" part of the log entry.
		template <typename T, typename std::enable_if<std::is_class<
			std::remove_reference<decltype(std::stringstream() << std::decay<T>::type())>>::value, int>::type = 0>
		log_entry& operator << (const T& v)
		{
			message_ << v;

			return *this;
		}

		log_level level() const
		{
			return level_;
		}

		~log_entry();
		
	private:
		logger& logger_instance_;
		log_level level_;
		lograffe::fields entry_fields_;
		std::stringstream message_;
	};

}
