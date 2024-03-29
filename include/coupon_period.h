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

#include <period.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <chrono>
#include <vector>
#include <memory>


namespace coupon_schedule
{

	class coupon_period
	{

	public:

		coupon_period() noexcept = delete;
		coupon_period(const coupon_period&) = default;
		coupon_period(coupon_period&&) noexcept = default;

		coupon_period(
			gregorian::days_period period,
			std::chrono::year_month_day pay,
			std::chrono::year_month_day ex_div
		) noexcept;

		coupon_period(
			gregorian::days_period period,
			std::chrono::year_month_day pay
		) noexcept;

		coupon_period(
			gregorian::days_period period,
			const gregorian::calendar& cal,
			const gregorian::business_day_convention* const bdc = &gregorian::Following
		);

		~coupon_period() noexcept = default;

		coupon_period& operator=(const coupon_period&) = default;
		coupon_period& operator=(coupon_period&&) noexcept = default;

	public:

		friend auto operator==(const coupon_period& p1, const coupon_period& p2) noexcept -> bool = default;

	public:

		auto get_period() const noexcept -> const gregorian::days_period&;
		auto get_pay_date() const noexcept -> const std::chrono::year_month_day&;
		auto get_ex_div_date() const noexcept -> const std::chrono::year_month_day&;

	public:

		auto get_accrual_start_date() const noexcept -> const std::chrono::year_month_day&;
		auto get_accrual_end_date() const noexcept -> const std::chrono::year_month_day&;

	private:

		gregorian::days_period _period;

		std::chrono::year_month_day _pay; // is it clear that this is a date?
		std::chrono::year_month_day _ex_div; // is it clear that this is a date?

	};



	using coupon_periods = std::vector<coupon_period>; // is this the right data structure?



	inline coupon_period::coupon_period(
		gregorian::days_period period,
		std::chrono::year_month_day pay,
		std::chrono::year_month_day ex_div
	) noexcept :
		_period{ std::move(period) },
		_pay{ std::move(pay) },
		_ex_div{ std::move(ex_div) }
	{
		// should we check that the ex-div date at least "makes sense" against other dates available here?
	}


	inline coupon_period::coupon_period(
		gregorian::days_period period,
		std::chrono::year_month_day pay
	) noexcept :
		_period{ std::move(period) },
		_pay{ std::move(pay) },
		_ex_div{ _period.get_until()}
	{
	}


	// should there also be a version with ex_divs? (for Gilts for example)
	// could be that the adjustment for a good payment date should be outside coupon_period
	inline coupon_period::coupon_period(
		gregorian::days_period period,
		const gregorian::calendar& cal,
		const gregorian::business_day_convention* const bdc
	) :
		_period{ std::move(period) },
		_pay{ bdc->adjust(_period.get_until(), cal) },
		_ex_div{ _period.get_until() }
	{
	}



	inline auto coupon_period::get_period() const noexcept -> const gregorian::days_period&
	{
		return _period;
	}


	inline auto coupon_period::get_pay_date() const noexcept -> const std::chrono::year_month_day&
	{
		return _pay;
	}


	inline auto coupon_period::get_ex_div_date() const noexcept -> const std::chrono::year_month_day&
	{
		return _ex_div;
	}



	inline auto coupon_period::get_accrual_start_date() const noexcept -> const std::chrono::year_month_day&
	{
		return _period.get_from();
	}


	inline auto coupon_period::get_accrual_end_date() const noexcept -> const std::chrono::year_month_day&
	{
		return _period.get_until();
	}

}
