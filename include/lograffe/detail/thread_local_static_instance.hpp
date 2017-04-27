//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

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
			return current_thread_instance_;
		}

		static void set_current(T&& new_instance) noexcept
		{
			T old_instance = std::move(current_thread_instance_);
			current_thread_instance_ = std::move(new_instance);
			new_instance = std::move(old_instance);
		}

		static void reset_current() noexcept
		{
			current_thread_instance_ = T();
		}

	private:
		static thread_local T current_thread_instance_;
	};

	template<typename T>
	thread_local T thread_local_static_instance<T>::current_thread_instance_;

}

}
