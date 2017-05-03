//
// lograffe logging library.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <lograffe/field.hpp>
#include <initializer_list>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

namespace lograffe
{

	class fields
	{
	public:
		fields(std::initializer_list<field> members)
			: members_(members)
		{}

		fields()
			: members_()
		{}

		fields(const fields&) = default;
		fields(fields&&) = default;

		// delete assignment operators until we need them:
		fields& operator = (const fields&) = delete;
		fields& operator = (fields&&) = delete;

		void append(field&& other_field)
		{
			members_.emplace_back(std::move(other_field));
		}

		void append(const field& other_field)
		{
			members_.emplace_back(other_field);
		}

		void append(fields&& other_fields)
		{
			if (members_.empty())
			{
				members_ = std::move(other_fields.members_);
			}
			else
			{
				members_.reserve(members_.size() + other_fields.members_.size());

				std::move(other_fields.members_.begin(), other_fields.members_.end(), std::back_inserter(members_));
			}

			other_fields.members_.clear();
		}

		void append(const fields& other_fields)
		{
			members_.reserve(members_.size() + other_fields.members_.size());

			std::copy(other_fields.members_.begin(), other_fields.members_.end(), std::back_inserter(members_));
		}

		void for_each(std::function<void (const field&)> callback) const
		{
			std::for_each(members_.cbegin(), members_.cend(), callback);
		}

	private:
		std::vector<field> members_;
	};

}
