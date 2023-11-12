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

	// where should we consider schedules running on month end?

	// probably not the right place for these
	constexpr auto SemiAnnualy = std::chrono::months{ 6 };
	constexpr auto Quarterly = std::chrono::months{ 3 };
	constexpr auto Monthly = std::chrono::months{ 1 };


	template<typename freq>
	auto _increase_ymd_as_needed(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day effective,
		const freq& frequency
	) -> std::chrono::year_month_day
	{
		while (d + frequency <= effective)
			d += frequency;

		return d;
	}

	template<typename freq>
	auto _decrease_ymd_as_needed(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day effective,
		const freq& frequency
	) -> std::chrono::year_month_day
	{
		while (d > effective)
			d -= frequency;

		return d;
	}

	template<typename freq>
	auto _make_quasi_coupon_schedule_storage(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day maturity,
		const freq& frequency
	) -> gregorian::schedule::storage
	{
		auto s = gregorian::schedule::storage{};

		while (s.insert(d), d < maturity)
			d += frequency;

		return s;
	}


	// should "effective"/"maturity" be passed into as a period?
	template<typename freq> // I think the current implemetation would only compile for freq in months or years - too restrictive?
	auto make_quasi_coupon_schedule(
		std::chrono::year_month_day effective, // or should it be called "issue"?
		std::chrono::year_month_day maturity,
		const freq& frequency, // at the moment we are not thinking about tricky situations towards the end of month
		const std::chrono::month_day& anchor
	) -> gregorian::schedule
	{
		auto d = std::chrono::year_month_day{ effective.year(), anchor.month(), anchor.day() };

		if (d < effective)
			d = _increase_ymd_as_needed(d, effective, frequency);
		else if (d > effective)
			d = _decrease_ymd_as_needed(d, effective, frequency);
		// if d == effective no need to do anything more

		auto s = _make_quasi_coupon_schedule_storage(d, maturity, frequency);

		// we can assert that s is not empty
		auto p = gregorian::period{ *s.cbegin(), *s.crbegin() };

		return gregorian::schedule{	std::move(p), std::move(s) };
	}

}
