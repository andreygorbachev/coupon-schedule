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
#include <period.h>

#include <chrono>


namespace coupon_schedule
{

	class one_1 final : public day_count
	{

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	};


	const auto One1 = one_1{};



	class actual_actual final : public day_count
	{

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	};


	const auto ActualActual = actual_actual{};



	class actual_365_fixed final : public day_count
	{

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	};


	const auto Actual365Fixed = actual_365_fixed{};



	class actual_360 final : public day_count
	{

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	};


	const auto Actual360 = actual_360{};



	class thirty_360 final : public day_count
	{

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	};


	const auto Thirty360 = thirty_360{};



	class thirty_e_360 final : public day_count
	{

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	};


	const auto ThirtyE360 = thirty_e_360{};



	class thirty_e_360_isda final : public day_count
	{

	public:

		explicit thirty_e_360_isda(std::chrono::year_month_day termination) noexcept;

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	private:

		std::chrono::year_month_day _termination;

	};


//	const auto ThirtyE360ISDA = thirty_e_360_isda{};



	class actual_365_l final : public day_count
	{

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	};


	const auto Actual365L = actual_365_l{}; // or should it be Act365L? (looks like ISDA does not provide a "long" name)



	class calculation_252 final : public day_count
	{

	public:

		explicit calculation_252(const gregorian::calendar* const cal) noexcept;

	private:

		auto _fraction(const gregorian::days_period& period) const -> double final; // noexcept?

	private:

		const gregorian::calendar* _cal;

	};


//	const auto Calculation252 = calculation_252{};



	inline auto _actual(const gregorian::days_period& period) -> double
	{
		const auto dur = std::chrono::sys_days{ period.get_until() } - std::chrono::sys_days{ period.get_from() };
		return static_cast<double>(dur.count());
	}



	inline auto one_1::_fraction(const gregorian::days_period& period) const -> double
	{
		return 1.0;
	}



	inline auto actual_actual::_fraction(const gregorian::days_period& period) const -> double
	{
		const auto sy = period.get_from().year();
		const auto ey = period.get_until().year();

		if (sy == ey)
		{
			if (!sy.is_leap())
				return _actual(period) / 365.0;
			else
				return _actual(period) / 366.0;
		}
		else
		{
			auto result = 0.0;

			const auto td1 = std::chrono::year_month_day{ sy + std::chrono::years{ 1 }, std::chrono::January, std::chrono::day{ 1u } };
			if (!sy.is_leap())
				result += _actual({ period.get_from(), td1 }) / 365.0;
			else
				result += _actual({ period.get_from(), td1 }) / 366.0;

			const auto dur = ey - sy - std::chrono::years{ 1 };
			result += static_cast<double>(dur.count());

			const auto td2 = std::chrono::year_month_day{ ey, std::chrono::January, std::chrono::day{ 1u } };
			if (!ey.is_leap())
				result += _actual({ td2, period.get_until() }) / 365.0;
			else
				result += _actual({ td2, period.get_until() }) / 366.0;

			return result;
		}
	}



	inline auto actual_365_fixed::_fraction(const gregorian::days_period& period) const -> double
	{
		return _actual(period) / 365.0;
	}



	inline auto actual_360::_fraction(const gregorian::days_period& period) const -> double
	{
		return _actual(period) / 360.0;
	}



	inline auto thirty_360::_fraction(const gregorian::days_period& period) const -> double
	{
		const auto& start = period.get_from();
		auto sd = start.day();
		const auto sm = start.month();
		const auto sy = start.year();

		const auto& end = period.get_until();
		auto ed = end.day();
		const auto em = end.month();
		const auto ey = end.year();

		if (sd == std::chrono::day{ 31u })
			sd = std::chrono::day{ 30u };
		if (ed == std::chrono::day{ 31u } && sd > std::chrono::day{ 29u }) // at this stage sd might have changed, but the formula is still correct
			ed = std::chrono::day{ 30u };

		const auto nom =
			static_cast<double>((ey - sy).count()) * 360.0 +
			static_cast<double>((em - em).count()) * 30.0 +
			static_cast<double>((ed - sd).count());

		return nom / 360.0;
	}



	inline auto thirty_e_360::_fraction(const gregorian::days_period& period) const -> double
	{
		const auto& start = period.get_from();
		auto sd = start.day();
		const auto sm = start.month();
		const auto sy = start.year();

		const auto& end = period.get_until();
		auto ed = end.day();
		const auto em = end.month();
		const auto ey = end.year();

		if (sd == std::chrono::day{ 31u })
			sd = std::chrono::day{ 30u };
		if (ed == std::chrono::day{ 31u })
			ed = std::chrono::day{ 30u };

		const auto nom =
			static_cast<double>((ey - sy).count()) * 360.0 +
			static_cast<double>((em - em).count()) * 30.0 +
			static_cast<double>((ed - sd).count());

		return nom / 360.0;
	}



	inline thirty_e_360_isda::thirty_e_360_isda(std::chrono::year_month_day termination) noexcept :
		_termination{ termination }
	{
	}


	inline auto thirty_e_360_isda::_fraction(const gregorian::days_period& period) const -> double
	{
		const auto& start = period.get_from();
		auto sd = start.day();
		const auto sm = start.month();
		const auto sy = start.year();

		const auto& end = period.get_until();
		auto ed = end.day();
		const auto em = end.month();
		const auto ey = end.year();

		if (start == std::chrono::year_month_day_last{ sy, sm / std::chrono::last })
			sd = std::chrono::day{ 30u };
		if (end != _termination)
		{
			if (end == std::chrono::year_month_day_last{ ey, em / std::chrono::last })
				ed = std::chrono::day{ 30u };
		}
		else
		{
			if (em != std::chrono::February && end == std::chrono::year_month_day_last{ ey, em / std::chrono::last })
				ed = std::chrono::day{ 30u };
		}

		const auto nom =
			static_cast<double>((ey - sy).count()) * 360.0 +
			static_cast<double>((em - em).count()) * 30.0 +
			static_cast<double>((ed - sd).count());

		return nom / 360.0;
	}



	inline auto actual_365_l::_fraction(const gregorian::days_period& period) const -> double
	{
		const auto denom = !period.get_until().year().is_leap() ? 365.0 : 366.0;

		return _actual(period) / denom;
	}



	// we also need to think if start is included/excluded and if end is included/excluded
	inline calculation_252::calculation_252(const gregorian::calendar* const cal) noexcept :
		_cal{ cal }
	{
	}


	inline auto calculation_252::_fraction(const gregorian::days_period& period) const -> double
	{
		return static_cast<double>(_cal->count_business_days(period)) / 252.0;
	}

}
