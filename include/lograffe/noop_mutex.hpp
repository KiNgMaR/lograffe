//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

namespace lograffe
{

	// This class satisfies the BasicLockable concept. It can be used
	// to turn off locking mechanisms within sinks, making them faster
	// but no longer safe for concurrent access from different threads.
	class noop_mutex
	{
	public:
		void lock() const noexcept {}
		void unlock() const noexcept {}
	};

}
