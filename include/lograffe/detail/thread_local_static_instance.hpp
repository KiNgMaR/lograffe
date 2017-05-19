//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <memory>
#include <functional>

namespace lograffe
{

namespace detail
{

	// This is a helper class to facilitate a static thread local singleton
	// of type T within a header-only library. T must be default-constructible.
	template<typename T>
	class thread_local_static_instance
	{
	public:
		static T& current() noexcept
		{
			if (current_thread_instance_)
			{
				return *current_thread_instance_;
			}
			else if (default_logger_creation_)
			{
				current_thread_instance_ = std::move(default_logger_creation_());

				return *current_thread_instance_;
			}
			else
			{
				static T default_constructed_logger;
				// There's a catch here. Normally a logger can assume to be accessed from
				// only one thread at a time. However, with this static default constructed
				// thing, this assumption breaks!

				return default_constructed_logger;
			}
		}

		static void set_current(T&& new_instance) noexcept
		{
			current_thread_instance_.reset(std::move(new_instance));
		}

		static void reset_current() noexcept
		{
			current_thread_instance_.reset();
		}

		static void set_global_default_creation_method(const std::function<std::unique_ptr<T> ()>& functor)
		{
			default_logger_creation_ = functor;
		}

	private:
		static thread_local std::unique_ptr<T> current_thread_instance_;
		static std::function<std::unique_ptr<T> ()> default_logger_creation_;
	};

	template<typename T>
	/*static*/ thread_local std::unique_ptr<T> thread_local_static_instance<T>::current_thread_instance_;

	template<typename T>
	/*static*/ std::function<std::unique_ptr<T> ()> thread_local_static_instance<T>::default_logger_creation_;

}

}
