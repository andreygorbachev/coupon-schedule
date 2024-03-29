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

#include <coupon_period.h>
#include <coupon_schedule.h>
#include <quasi_coupon_schedule.h>

#include <calendar.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace gregorian;

using namespace std::chrono;


namespace coupon_schedule
{
/*
	TEST(coupon_schedule, make_coupon_schedule)
	{
		const auto expected = coupon_periods{
			{ { 2023y / January / 1d, 2023y / June / 7d }, 2023y / June / 7d },
			{ { 2023y / June / 7d, 2023y / December / 7d }, 2023y / December / 7d },
		};

		const auto cal = make_calendar_england();

		const auto gilt_coupon_schedule = make_coupon_schedule(
			make_quasi_coupon_schedule(
				{ 2023y / January / 1d,	2023y / December / 7d },
				SemiAnnualy,
				June / 7d
			),
			cal
		);

		EXPECT_EQ(expected, gilt_coupon_schedule);
	}
*/
}
