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

#include "setup.h"

#include <compounding_period.h>
#include <compounding_schedule.h>
#include <coupon_period.h>

#include <calendar.h>

#include <gtest/gtest.h>

#include <chrono>

//using namespace calendar;

using namespace std::chrono;


namespace coupon_schedule
{

	TEST(compounding_schedule, make_overnight_maturity)
	{
		const auto publication = calendar::calendar{
			calendar::SaturdaySundayWeekend,
			calendar::schedule{
				calendar::period{ 2023y / May / 26d, 2023y / May / 30d },
				{ 2023y / May / 29d }
			}
		};

		EXPECT_EQ(2023y / May / 30d, make_overnight_maturity(2023y / May / 26d, publication));
	}

	TEST(compounding_schedule, make_compounding_schedule1)
	{
		const auto expected = compounding_periods{
			{ { 2023y / June / 1d, 2023y / June / 2d }, 2023y / June / 1d },
			{ { 2023y / June / 2d, 2023y / June / 5d }, 2023y / June / 2d },
			{ { 2023y / June / 5d, 2023y / June / 6d }, 2023y / June / 5d },
			{ { 2023y / June / 6d, 2023y / June / 7d }, 2023y / June / 6d },
			{ { 2023y / June / 7d, 2023y / June / 8d }, 2023y / June / 7d },
		};

		const auto period = coupon_period{
			{ 2023y / June / 1d, 2023y / June / 8d },
			2023y / June / 8d
		};

		const auto cal = make_calendar_england();

		const auto compounding_schedule = make_compounding_schedule(period, cal);

		EXPECT_EQ(expected, compounding_schedule);
	}

	TEST(compounding_schedule, make_compounding_schedule2)
	{
		// non-standard first period
		const auto expected = compounding_periods{
			{ { 2023y / June / 3d, 2023y / June / 5d }, 2023y / June / 2d },
			{ { 2023y / June / 5d, 2023y / June / 6d }, 2023y / June / 5d },
			{ { 2023y / June / 6d, 2023y / June / 7d }, 2023y / June / 6d },
			{ { 2023y / June / 7d, 2023y / June / 8d }, 2023y / June / 7d },
		};

		const auto period = coupon_period{
			{ 2023y / June / 3d, 2023y / June / 8d },
			2023y / June / 8d
		};

		const auto cal = make_calendar_england();

		const auto compounding_schedule = make_compounding_schedule(period, cal);

		EXPECT_EQ(expected, compounding_schedule);
	}

	TEST(compounding_schedule, make_compounding_schedule3)
	{
		// non-standard last period
		const auto expected = compounding_periods{
			{ { 2023y / June / 1d, 2023y / June / 2d }, 2023y / June / 1d },
			{ { 2023y / June / 2d, 2023y / June / 4d }, 2023y / June / 2d },
		};

		const auto period = coupon_period{
			{ 2023y / June / 1d, 2023y / June / 4d },
			2023y / June / 8d
		};

		const auto cal = make_calendar_england();

		const auto compounding_schedule = make_compounding_schedule(period, cal);

		EXPECT_EQ(expected, compounding_schedule);
	}

	TEST(compounding_schedule, make_compounding_schedule4)
	{
		// non-standard first period, which is also a non-standard last period
		const auto expected = compounding_periods{
			{ { 2023y / June / 3d, 2023y / June / 4d }, 2023y / June / 2d },
		};

		const auto period = coupon_period{
			{ 2023y / June / 3d, 2023y / June / 4d },
			2023y / June / 8d
		};

		const auto cal = make_calendar_england();

		const auto compounding_schedule = make_compounding_schedule(period, cal);

		EXPECT_EQ(expected, compounding_schedule);
	}

	TEST(compounding_schedule, make_compounding_schedule5)
	{
		// compounding schedule for an empty coupon period
		const auto expected = compounding_periods{
			{ { 2023y / June / 1d, 2023y / June / 1d }, 2023y / June / 1d }, // or should it be an exception?
		};

		const auto period = coupon_period{
			{ 2023y / June / 1d, 2023y / June / 1d },
			2023y / June / 8d
		};

		const auto cal = make_calendar_england();

		const auto compounding_schedule = make_compounding_schedule(period, cal);

		EXPECT_EQ(expected, compounding_schedule);
	}

}
