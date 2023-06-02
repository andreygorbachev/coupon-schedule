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

#include <annual_holidays.h>
#include <weekend.h>
#include <schedule.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <chrono>
#include <unordered_set>


namespace coupon_schedule
{

	inline auto make_holiday_schedule_england() -> calendar::schedule
	{
		using namespace calendar;

		const auto EarlyMayBankHoliday = weekday_indexed_holiday{ std::chrono::May / std::chrono::Monday[1] };
		const auto SpringBankHoliday = weekday_last_holiday{ std::chrono::May / std::chrono::Monday[std::chrono::last] };
		const auto SummerBankHoliday = weekday_last_holiday{ std::chrono::August / std::chrono::Monday[std::chrono::last] };

		auto rules = std::unordered_set<const annual_holiday*>{};
		rules.insert(&NewYearsDay);
		rules.insert(&GoodFriday);
		rules.insert(&EasterMonday);
		rules.insert(&EarlyMayBankHoliday);
		rules.insert(&SpringBankHoliday);
		rules.insert(&SummerBankHoliday);
		rules.insert(&ChristmasDay);
		rules.insert(&BoxingDay);

		const auto hs2018_2019 = make_holiday_schedule(
			std::chrono::year{ 2018 },
			std::chrono::year{ 2019 },
			rules
		);

		const auto VictoryInEuropeDay = named_holiday{ std::chrono::May / std::chrono::day{ 8u } };

		auto rules2020 = std::unordered_set<const annual_holiday*>{};
		rules2020.insert(&NewYearsDay);
		rules2020.insert(&GoodFriday);
		rules2020.insert(&EasterMonday);
		rules2020.insert(&VictoryInEuropeDay);
		rules2020.insert(&SpringBankHoliday);
		rules2020.insert(&SummerBankHoliday);
		rules2020.insert(&ChristmasDay);
		rules2020.insert(&BoxingDay);

		const auto hs2020 = make_holiday_schedule(
			std::chrono::year{ 2020 },
			std::chrono::year{ 2020 },
			rules2020
		);

		const auto hs2021 = make_holiday_schedule(
			std::chrono::year{ 2021 },
			std::chrono::year{ 2021 },
			rules
		);

		const auto SpringBankHoliday2 = named_holiday{ std::chrono::June / std::chrono::day{ 2u } };
		const auto PlatinumJubileeHoliday = named_holiday{ std::chrono::June / std::chrono::day{ 3u } };
		const auto StateFuneral = named_holiday{ std::chrono::September / std::chrono::day{ 19u } }; // Bank Holiday for the State Funeral of Queen Elizabeth II

		auto rules2022 = std::unordered_set<const annual_holiday*>{};
		rules2022.insert(&NewYearsDay);
		rules2022.insert(&GoodFriday);
		rules2022.insert(&EasterMonday);
		rules2022.insert(&EarlyMayBankHoliday);
		rules2022.insert(&SpringBankHoliday2);
		rules2022.insert(&PlatinumJubileeHoliday);
		rules2022.insert(&SummerBankHoliday);
		rules2022.insert(&StateFuneral);
		rules2022.insert(&ChristmasDay);
		rules2022.insert(&BoxingDay);

		const auto hs2022 = make_holiday_schedule(
			std::chrono::year{ 2022 },
			std::chrono::year{ 2022 },
			rules2022
		);

		const auto Coronation = named_holiday{ std::chrono::May / std::chrono::day{ 8u } }; // Bank holiday for the coronation of King Charles III

		auto rules2023 = std::unordered_set<const annual_holiday*>{};
		rules2023.insert(&NewYearsDay);
		rules2023.insert(&GoodFriday);
		rules2023.insert(&EasterMonday);
		rules2023.insert(&EarlyMayBankHoliday);
		rules2023.insert(&Coronation);
		rules2023.insert(&SpringBankHoliday);
		rules2023.insert(&SummerBankHoliday);
		rules2023.insert(&ChristmasDay);
		rules2023.insert(&BoxingDay);

		const auto hs2023 = make_holiday_schedule(
			std::chrono::year{ 2023 },
			std::chrono::year{ 2023 },
			rules2023
		);

		const auto hs2024_2025 = make_holiday_schedule(
			std::chrono::year{ 2024 },
			std::chrono::year{ 2025 },
			rules
		);

		return hs2018_2019 + hs2020 + hs2021 + hs2022 + hs2023 + hs2024_2025;
	}


	inline auto make_calendar_england() -> calendar::calendar
	{
		auto cal = calendar::calendar{
			calendar::SaturdaySundayWeekend,
			make_holiday_schedule_england()
		};
		cal.substitute(&calendar::Following);

		return cal;
	}


	inline auto make_holiday_schedule_brazil() -> calendar::schedule
	{
		using namespace calendar;

		// nationwide holidays

		const auto TiradentesDay = named_holiday{ std::chrono::April / std::chrono::day{ 21u } };
		const auto LabourDay = named_holiday{ std::chrono::May / std::chrono::day{ 1u } }; // should this be in calendar?
		const auto IndependenceDay = named_holiday{ std::chrono::September / std::chrono::day{ 7u } };
		const auto OurLadyOfAparecida = named_holiday{ std::chrono::October / std::chrono::day{ 12u } };
		const auto AllSoulsDay = named_holiday{ std::chrono::November / std::chrono::day{ 2u } };
		const auto RepublicProclamationDay = named_holiday{ std::chrono::November / std::chrono::day{ 15u } };

		auto rules = std::unordered_set<const annual_holiday*>{};
		rules.insert(&NewYearsDay);
		rules.insert(&TiradentesDay);
		rules.insert(&LabourDay);
		rules.insert(&IndependenceDay);
		rules.insert(&OurLadyOfAparecida);
		rules.insert(&AllSoulsDay);
		rules.insert(&RepublicProclamationDay);
		rules.insert(&ChristmasDay);
		// we should also consider election days (but as they are always on Sundays it probably does not matter here)

		const auto hs2018_2025 = make_holiday_schedule(
			std::chrono::year{ 2018 },
			std::chrono::year{ 2025 },
			rules
		);

		return hs2018_2025;
	}


	inline auto make_calendar_brazil() -> calendar::calendar
	{
		auto cal = calendar::calendar{
			calendar::SaturdaySundayWeekend,
			make_holiday_schedule_brazil()
		};
		cal.substitute(&calendar::NoAdjustment); // make it explicit that no adjustment is needed

		return cal;
	}

}
