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

#include "duration_variant.h"

#include <schedule.h>

#include <chrono>
#include <memory>


namespace coupon_schedule
{

	// where should we consider schedules running on month end?

	// probably not the right place for these
	constexpr auto SemiAnnualy = duration_variant{ std::chrono::months{ 6 } };
	constexpr auto Quarterly = duration_variant{ std::chrono::months{ 3 } };
	constexpr auto Monthly = duration_variant{ std::chrono::months{ 1 } };


	inline auto _increase_ymd_as_needed(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day& issue,
		const duration_variant& frequency
	) -> std::chrono::year_month_day
	{
		while (advance(d, frequency) <= issue)
			d = advance(d, frequency);

		return d;
	}

	inline auto _decrease_ymd_as_needed(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day& issue,
		const duration_variant& frequency
	) -> std::chrono::year_month_day
	{
		while (d > issue)
			d = retreat(d, frequency);

		return d;
	}

	inline auto _make_quasi_coupon_schedule_storage(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day& maturity,
		const duration_variant& frequency
	) -> gregorian::schedule::storage
	{
		auto s = gregorian::schedule::storage{};

		while (s.insert(d), d < maturity)
			d = advance(d, frequency);

		return s;
	}


	inline auto make_quasi_coupon_schedule(
		const gregorian::days_period& issue_maturity,
		const duration_variant& frequency, // at the moment we are not thinking about tricky situations towards the end of month
		const std::chrono::month_day& anchor
	) -> gregorian::schedule
	{
		const auto& issue = issue_maturity.get_from();
		const auto& maturity = issue_maturity.get_until();

		auto d = std::chrono::year_month_day{ issue.year(), anchor.month(), anchor.day() };

		if (d < issue)
			d = _increase_ymd_as_needed(d, issue, frequency);
		else if (d > issue)
			d = _decrease_ymd_as_needed(d, issue, frequency);
		else
			; // if d == issue no need to do anything more

		auto s = _make_quasi_coupon_schedule_storage(d, maturity, frequency);

		// we can assert that s is not empty
		auto p = gregorian::period{ *s.cbegin(), *s.crbegin() };

		return gregorian::schedule{	std::move(p), std::move(s) };
	}

}
