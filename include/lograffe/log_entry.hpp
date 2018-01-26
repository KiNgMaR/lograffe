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
#include <lograffe/log_entry_flags.hpp>
#include <sstream>
#include <chrono>

namespace lograffe
{
	class logger;

	class log_entry
	{
	public:
		log_entry(logger& logger_instance, log_level level, const char* level_name)
			: logger_instance_(logger_instance)
			, level_(level)
			, level_name_(level_name)
			, timestamp_{ std::chrono::system_clock::now() }
			, entry_fields_{}
			, message_()
			, flags_()
		{}

		log_entry() = delete;

		// for efficiency, we only want to std::move instances of this class.
		log_entry(const log_entry&) = delete;
		log_entry& operator = (const log_entry&) = delete;

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

		// This shift operator is used to append things to the "message" part of the log entry.
		// It is enabled for all types that work with stringstream's operator <<.
		template <typename T, typename std::enable_if<std::is_class<
			std::remove_reference<decltype(std::stringstream() << typename std::decay<T>::type())>>::value, int>::type = 0>
		log_entry& operator << (const T& v)
		{
			message_ << v;

			return *this;
		}

		log_entry& operator << (log_entry_flags bit)
		{
			flags_ = flags_ | bit;

			return *this;
		}

		log_level level() const
		{
			return level_;
		}

		const char* level_name() const
		{
			return level_name_;
		}

		const std::chrono::system_clock::time_point& timestamp_ref() const
		{
			return timestamp_;
		}

		const lograffe::fields& fields_ref() const
		{
			return entry_fields_;
		}

		const std::stringstream& message_ref() const
		{
			return message_;
		}

		bool has_flag(log_entry_flags bit) const
		{
			return (flags_ & bit) == bit;
		}

		~log_entry();
		
	private:
		// keep a reference to a logger so we know where to send the complete entry
		logger& logger_instance_;

        const log_level level_;
        // this is totally safe because it is expected to contain references to
		// compile-time constants only:
		const char* level_name_;

        // log entry payload goes here:
		const std::chrono::system_clock::time_point timestamp_;
		lograffe::fields entry_fields_;
		std::stringstream message_;
		log_entry_flags flags_;
	};

}
