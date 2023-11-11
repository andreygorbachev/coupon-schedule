// The MIT License (MIT)
//
// Copyright (c) 2023 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "coupon_period.h"
#include "quasi_coupon_schedule.h"

#include <period.h>
#include <schedule.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <chrono>
#include <memory>


namespace coupon_schedule
{

	inline auto _make_coupon_schedule(const gregorian::schedule& qcs) -> coupon_periods
	{
		auto result = coupon_periods{};

		const auto& f = qcs.get_from_until().get_from();
		const auto& u = qcs.get_from_until().get_until();
		const auto& d = qcs.get_dates();

		// naive implementation for now
		if (f == u)
		{
			result.emplace_back(
				gregorian::period{ f, u },
				std::chrono::year_month_day{},
				std::chrono::year_month_day{}
			);
		}
		else
		{
			auto dates = d;
			dates.insert(f);
			dates.insert(u);

			auto i = dates.cbegin();
			auto prev = *i;
			++i;
			while (i != dates.cend())
			{
				result.emplace_back(
					gregorian::period{ prev, *i },
					std::chrono::year_month_day{},
					std::chrono::year_month_day{}
				);
				prev = *i;
				++i;
			}
		}

		return result;
	}


	// at the moment long coupons are not supported
	inline auto make_coupon_schedule(const gregorian::schedule& qcs, const gregorian::calendar& c) -> coupon_periods // bad name as we are not actually creating a schedule (just a verctor of periods)
	{
		auto result = _make_coupon_schedule(qcs);

		// adjust for good payment dates
		for (auto& p : result)
			p._pay = gregorian::Following.adjust(p._period.get_until(), c); // in the future allow for other adjustments, not just following

		// what do we need to do about ex-divs here?

		return result;
	}

}
