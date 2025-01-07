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

#include <annual_holidays.h>
#include <weekend.h>
#include <schedule.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <chrono>

using namespace gregorian;

using namespace std;
using namespace std::chrono;


namespace coupon_schedule
{

	inline auto make_holiday_schedule_england() -> schedule
	{
		const auto EarlyMayBankHoliday = weekday_indexed_holiday{ May / Monday[1] };
		const auto SpringBankHoliday = weekday_last_holiday{ May / Monday[last] };
		const auto SummerBankHoliday = weekday_last_holiday{ August / Monday[last] };

		auto rules = annual_holiday_storage{
			&NewYearsDay,
			&GoodFriday,
			&EasterMonday,
			&EarlyMayBankHoliday,
			&SpringBankHoliday,
			&SummerBankHoliday,
			&ChristmasDay,
			&BoxingDay
		};

		const auto hs2018_2019 = make_holiday_schedule(
			years_period{ 2018y, 2019y },
			rules
		);

		const auto VictoryInEuropeDay = named_holiday{ May / 8d };

		auto rules2020 = annual_holiday_storage{
			&NewYearsDay,
			&GoodFriday,
			&EasterMonday,
			&VictoryInEuropeDay,
			&SpringBankHoliday,
			&SummerBankHoliday,
			&ChristmasDay,
			&BoxingDay
		};

		const auto hs2020 = make_holiday_schedule(
			2020y,
			rules2020
		);

		const auto hs2021 = make_holiday_schedule(
			2021y,
			rules
		);

		const auto SpringBankHoliday2 = named_holiday{ June / 2d };
		const auto PlatinumJubileeHoliday = named_holiday{ June / 3d };
		const auto StateFuneral = named_holiday{ September / 19d }; // Bank Holiday for the State Funeral of Queen Elizabeth II

		auto rules2022 = annual_holiday_storage{
			&NewYearsDay,
			&GoodFriday,
			&EasterMonday,
			&EarlyMayBankHoliday,
			&SpringBankHoliday2,
			&PlatinumJubileeHoliday,
			&SummerBankHoliday,
			&StateFuneral,
			&ChristmasDay,
			&BoxingDay
		};

		const auto hs2022 = make_holiday_schedule(
			2022y,
			rules2022
		);

		const auto Coronation = named_holiday{ May / 8d }; // Bank holiday for the coronation of King Charles III

		auto rules2023 = annual_holiday_storage{
			&NewYearsDay,
			&GoodFriday,
			&EasterMonday,
			&EarlyMayBankHoliday,
			&Coronation,
			&SpringBankHoliday,
			&SummerBankHoliday,
			&ChristmasDay,
			&BoxingDay
		};

		const auto hs2023 = make_holiday_schedule(
			2023y,
			rules2023
		);

		const auto hs2024_2025 = make_holiday_schedule(
			years_period{ 2024y, 2025y },
			rules
		);

		return hs2018_2019 + hs2020 + hs2021 + hs2022 + hs2023 + hs2024_2025;
	}


	inline auto make_calendar_england() -> calendar
	{
		auto cal = calendar{
			SaturdaySundayWeekend,
			make_holiday_schedule_england()
		};
		cal.substitute(Following);

		return cal;
	}


	inline auto make_holiday_schedule_brazil() -> schedule
	{
		// nationwide holidays

		const auto TiradentesDay = named_holiday{ April / 21d };
		const auto LabourDay = named_holiday{ May / 1d }; // should this be in calendar?
		const auto IndependenceDay = named_holiday{ September / 7d };
		const auto OurLadyOfAparecida = named_holiday{ October / 12d };
		const auto AllSoulsDay = named_holiday{ November / 2d };
		const auto RepublicProclamationDay = named_holiday{ November / 15d };

		auto rules = annual_holiday_storage{
			&NewYearsDay,
			&TiradentesDay,
			&LabourDay,
			&IndependenceDay,
			&OurLadyOfAparecida,
			&AllSoulsDay,
			&RepublicProclamationDay,
			&ChristmasDay
		};
		// we should also consider election days (but as they are always on Sundays it probably does not matter here)

		const auto hs2018_2025 = make_holiday_schedule(
			years_period{ 2018y, 2025y },
			rules
		);

		return hs2018_2025;
	}


	inline auto make_calendar_brazil() -> calendar
	{
		auto cal = calendar{
			SaturdaySundayWeekend,
			make_holiday_schedule_brazil()
		};
		cal.substitute(NoAdjustment); // make it explicit that no adjustment is needed

		return cal;
	}

}
