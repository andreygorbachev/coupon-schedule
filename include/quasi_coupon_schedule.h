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

#include <schedule.h>

#include <chrono>
#include <memory>


namespace coupon_schedule
{

	// probably not the right place for these
	constexpr auto SemiAnnualy = std::chrono::months{ 6 };
	constexpr auto Quarterly = std::chrono::months{ 3 };
	constexpr auto Monthly = std::chrono::months{ 1 };


	// at the moment long coupons are not supported
	template<typename freq> // I think the current implemetation would only compile for freq in months or years - too restrictive?
	auto make_quasi_coupon_schedule(
		std::chrono::year_month_day effective, // or should it be called an issue?
		std::chrono::year_month_day maturity,
		const freq& frequency, // at the moment we are not thinking about tricky situations towards the end of month
		const std::chrono::month_day& anchor
	) -> calendar::schedule
	{
		auto s = calendar::schedule::storage{};

		auto d = std::chrono::year_month_day{ effective.year(), anchor.month(), anchor.day() };

		// in case the anchor is several periods after the effective
		while (d > effective)
			d -= frequency;

		// in case the anchor is several periods before the effective
		while (d < effective)
			d += frequency;

		while (d <= maturity)
		{
			s.insert(d);
			d += frequency;
		}

		return calendar::schedule{
			std::move(effective),
			std::move(maturity),
			std::move(s)
		};
	}

}
