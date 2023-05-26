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

#include <day_counts.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std;
using namespace std::chrono;


namespace coupon_schedule
{

	TEST(one_1, fraction)
	{
		EXPECT_DOUBLE_EQ(1.0, One1.fraction(2023y / January / 1d, 2023y / January / 2d));
		EXPECT_THROW(One1.fraction(2023y / January / 2d, 2023y / January / 1d), out_of_range);
	}

	TEST(actual_actual, fraction)
	{
		EXPECT_DOUBLE_EQ(1.0 / 365.0, ActualActual.fraction(2023y / January / 1d, 2023y / January / 2d));
	}

	TEST(actual_365_fixed, fraction)
	{
		EXPECT_DOUBLE_EQ(1.0 / 365.0, Actual365Fixed.fraction(2023y / January / 1d, 2023y / January / 2d));
	}

	TEST(actual_360, fraction)
	{
		EXPECT_DOUBLE_EQ(1.0 / 360.0, Actual360.fraction(2023y / January / 1d, 2023y / January / 2d));
	}

	TEST(thirty_360, fraction)
	{
		EXPECT_DOUBLE_EQ(1.0 / 360.0, Thirty360.fraction(2023y / January / 1d, 2023y / January / 2d));
	}

	TEST(thirty_e_360, fraction)
	{
		EXPECT_DOUBLE_EQ(1.0 / 360.0, ThirtyE360.fraction(2023y / January / 1d, 2023y / January / 2d));
	}

	TEST(actual_365_l, fraction)
	{
		EXPECT_DOUBLE_EQ(1.0 / 365.0, Actual365L.fraction(2023y / January / 1d, 2023y / January / 2d));
		EXPECT_DOUBLE_EQ(1.0 / 366.0, Actual365L.fraction(2020y / January / 1d, 2020y / January / 2d));
	}

	TEST(calculation_252, fraction)
	{
		const auto cal = make_calendar_brazil();
		const auto dc = calculation_252{ &cal };

		EXPECT_DOUBLE_EQ(1.0 / 252.0, dc.fraction(2023y / January / 1d, 2023y / January / 2d));
	}

}
