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

#include "compounding_period.h"
#include "coupon_period.h"

#include <period.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <chrono>
#include <memory>


namespace coupon_schedule
{

	inline auto make_overnight_maturity(
		const std::chrono::year_month_day& effective,
		const calendar::calendar& publication
	) -> std::chrono::year_month_day
	{
		return calendar::Following.adjust(
			std::chrono::sys_days{ effective } + std::chrono::days{ 1 },
			publication
		);
	}
	// or should we do from/until instead of effective/maturity?


	// naive, recursive implementation for now
	inline auto _make_compounding_schedule(const coupon_period& cp, const calendar::calendar& c) -> compounding_periods
	{
		const auto& f = cp._period.get_from();
		const auto& u = cp._period.get_until();

		const auto effective = f;
		const auto maturity = make_overnight_maturity(effective, c);
		if (maturity < u)
		{
			auto result = _make_compounding_schedule(coupon_period{ calendar::period{ maturity, u }, cp._pay }, c);

			result.emplace(result.begin(), calendar::period{ effective, maturity }, std::chrono::year_month_day{});

			return result;
		}
		else
		{
			auto result = compounding_periods{};

			result.emplace_back(calendar::period{ f, u }, std::chrono::year_month_day{});

			return result;
		}
	}
	// or should it be a generic "1d" schedule adjuste for good business days? (so nothin special is needed for business days?)


	inline auto make_compounding_schedule(const coupon_period& cp, const calendar::calendar& c) -> compounding_periods // bad name as we are not actually creating a schedule (just a verctor of periods)
	{
		auto result = _make_compounding_schedule(cp, c); // we assume that the compounding calendar and reset calendar are the same (is it true for SOFR?)

		// adjust for good reset dates
		for (auto& p : result)
			p._reset = calendar::Preceding.adjust(p._period.get_from(), c);

		return result;
	}

}
