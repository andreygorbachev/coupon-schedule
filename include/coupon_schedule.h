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

#include "period.h"
#include "quasi_coupon_schedule.h"

#include <schedule.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <chrono>
#include <memory>


namespace coupon_schedule
{

	inline auto _make_coupon_schedule(const calendar::schedule& qcs) -> periods
	{
		auto result = periods{};

		const auto& f = qcs.get_front();
		const auto& b = qcs.get_back();
		const auto& hols = qcs.get_hols(); // get_hols needs a better name

		// naive implementation for now
		if (f == b)
		{
			result.emplace_back(f, b, b);
		}
		else
		{
			auto dates = hols;
			dates.insert(f);
			dates.insert(b);

			auto i = dates.cbegin();
			auto prev = *i;
			++i;
			while (i != dates.cend())
			{
				result.emplace_back(prev, *i, *i);
				prev = *i;
				++i;
			}
		}

		return result;
	}


	inline auto make_coupon_schedule(const calendar::schedule& qcs, const calendar::calendar& c) -> periods
	{
		auto result = _make_coupon_schedule(qcs);

		// adjust for good payment dates
		for (auto& p : result)
			p._pay = calendar::Following.adjust(p._end, c);

		return result;
	}

}
