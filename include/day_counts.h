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

#include "day_count_interface.h"

#include <calendar.h>

#include <chrono>


namespace coupon_schedule
{

	class one_1 final : public day_count
	{

	private:

		auto _numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int final; // noexcept?
		auto _denominator() const noexcept -> int final;

	};


	const auto One1 = one_1{};



	class actual_365_fixed final : public day_count
	{

	private:

		auto _numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int final; // noexcept?
		auto _denominator() const noexcept -> int final;

	};


	const auto Actual365Fixed = actual_365_fixed{};



	class actual_360 final : public day_count
	{

	private:

		auto _numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int final; // noexcept?
		auto _denominator() const noexcept -> int final;

	};


	const auto Actual360 = actual_360{};



	class actual_365_l final : public day_count
	{

	private:

		auto _numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int final; // noexcept?
		auto _denominator() const noexcept -> int final;

	};


	const auto Actual365L = actual_365_l{}; // or should it be Act365L? (looks like ISDA does not provide a "long" name)



	class calculation_252 final : public day_count
	{

	public:

		explicit calculation_252(const calendar::calendar* const cal) noexcept;

	private:

		auto _numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int final; // noexcept?
		auto _denominator() const noexcept -> int final;

	private:

		const calendar::calendar* _cal;

	};


//	const auto Calculation252 = calculation_252{};



	auto one_1::_numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int
	{
		return 1;
	}


	auto one_1::_denominator() const noexcept -> int
	{
		return 1;
	}



	auto actual_365_fixed::_numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int
	{
		// assert that start <= end?
		const auto dur = std::chrono::sys_days{ end } - std::chrono::sys_days{ start };
		return dur.count();
	}


	auto actual_365_fixed::_denominator() const noexcept -> int
	{
		return 365;
	}



	auto actual_360::_numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int
	{
		// assert that start <= end?
		const auto dur = std::chrono::sys_days{ end } - std::chrono::sys_days{ start };
		return dur.count();
	}


	auto actual_360::_denominator() const noexcept -> int
	{
		return 360;
	}



	auto actual_365_l::_numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int
	{
		// assert that start <= end?
		const auto dur = std::chrono::sys_days{ end } - std::chrono::sys_days{ start };
		return dur.count();
	}


	auto actual_365_l::_denominator() const noexcept -> int
	{
		return 365; // temp only
	}



	// we also need to think if start is included/excluded and end is included/excluded
	calculation_252::calculation_252(const calendar::calendar* const cal) noexcept :
		_cal{ cal }
	{
	}


	auto calculation_252::_numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int
	{
		// assert that start <= end?
		return _cal->count_business_days(start, end);
	}


	auto calculation_252::_denominator() const noexcept -> int
	{
		return 252;
	}

}
