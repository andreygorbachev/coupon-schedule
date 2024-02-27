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

#include "date_adjuster_interface.h"

#include <chrono>


namespace coupon_schedule
{

	class not_after_quasi_coupon_date final : public date_adjuster // correct name?
	{

	private:

		virtual auto _adjust(
			const std::chrono::year_month_day& ymd,
			const duration_variant& frequency,
			const std::chrono::year_month_day& anchor
		) const -> std::chrono::year_month_day final;

	};


	const auto NotAfter = not_after_quasi_coupon_date{};



	class not_before_quasi_coupon_date final : public date_adjuster // should there be another layer like quasi_coupon_adjuster?
	{

	private:

		virtual auto _adjust(
			const std::chrono::year_month_day& ymd,
			const duration_variant& frequency,
			const std::chrono::year_month_day& anchor // should these 2 be captured by the constructor? (consider the same for cal in business_day_convention)
		) const -> std::chrono::year_month_day final;

	};


	const auto NotBefore = not_before_quasi_coupon_date{};



	inline auto _adjust_forward_not_after_quasi_coupon_date(
		const std::chrono::year_month_day& ymd,
		const duration_variant& frequency,
		const std::chrono::year_month_day& anchor
	) -> std::chrono::year_month_day
	{
		auto d = anchor; // for now assume that anchor is before ymd

		while (advance(d, frequency) <= ymd)
			d = advance(d, frequency);

		return d;
	}

	inline auto _adjust_backward_not_after_quasi_coupon_date(
		const std::chrono::year_month_day& ymd,
		const duration_variant& frequency,
		const std::chrono::year_month_day& anchor
	) -> std::chrono::year_month_day
	{
		auto d = anchor; // for now assume that anchor is before ymd

		while (advance(d, frequency) >= ymd)
			d = advance(d, frequency);

		return d;
	}

	inline auto not_after_quasi_coupon_date::_adjust(
		const std::chrono::year_month_day& ymd,
		const duration_variant& frequency,
		const std::chrono::year_month_day& anchor
	) const -> std::chrono::year_month_day
	{
		if(is_forward(frequency))
			return _adjust_forward_not_after_quasi_coupon_date(ymd, frequency, anchor);
		else
			return _adjust_backward_not_after_quasi_coupon_date(ymd, frequency, anchor); // also covers 0 frequency - what do we want to do there?
	}



	inline auto _adjust_forward_not_before_quasi_coupon_date(
		const std::chrono::year_month_day& ymd,
		const duration_variant& frequency,
		const std::chrono::year_month_day& anchor
	) -> std::chrono::year_month_day
	{
		auto d = anchor; // for now assume that anchor is after ymd

		while (d > ymd)
			d = retreat(d, frequency);

		return d;
	}

	inline auto _adjust_backward_not_before_quasi_coupon_date(
		const std::chrono::year_month_day& ymd,
		const duration_variant& frequency,
		const std::chrono::year_month_day& anchor
	) -> std::chrono::year_month_day
	{
		auto d = anchor; // for now assume that anchor is after ymd

		while (d < ymd)
			d = retreat(d, frequency);

		return d;
	}

	inline auto not_before_quasi_coupon_date::_adjust(
		const std::chrono::year_month_day& ymd,
		const duration_variant& frequency,
		const std::chrono::year_month_day& anchor
	) const -> std::chrono::year_month_day
	{
		if (is_forward(frequency))
			return _adjust_forward_not_before_quasi_coupon_date(ymd, frequency, anchor);
		else
			return _adjust_backward_not_before_quasi_coupon_date(ymd, frequency, anchor); // also covers 0 frequency - what do we want to do there?
	}

}
