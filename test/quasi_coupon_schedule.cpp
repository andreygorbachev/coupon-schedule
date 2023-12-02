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

#include <quasi_coupon_schedule.h>

#include <schedule.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace gregorian;

using namespace std::chrono;


namespace coupon_schedule
{

	TEST(quasi_coupon_schedule, make_quasi_coupon_schedule_1)
	{
		// basic usage
		const auto expected = schedule{
			{ 2022y / December / 7d, 2023y / December / 7d },
			schedule::storage{
				2022y / December / 7d,
				2023y / June / 7d,
				2023y / December / 7d,
			}
		};

		const auto gilt_quasi_coupon_schedule = make_quasi_coupon_schedule(
			{ 2023y / January / 1d,	2023y / December / 7d },
			SemiAnnualy,
			June / 7d
		);

		EXPECT_EQ(expected, gilt_quasi_coupon_schedule);
	}

	TEST(quasi_coupon_schedule, make_quasi_coupon_schedule_2)
	{
		// anchor is before the "from" ("from" is not on the quasi date strip)
		const auto expected = schedule{
			{ 2023y / June / 7d, 2023y / December / 7d },
			schedule::storage{
				2023y / June / 7d,
				2023y / December / 7d,
			}
		};

		const auto gilt_quasi_coupon_schedule = make_quasi_coupon_schedule(
			{ 2023y / July / 1d, 2023y / December / 7d },
			SemiAnnualy,
			June / 7d
		);

		EXPECT_EQ(expected, gilt_quasi_coupon_schedule);
	}

	TEST(quasi_coupon_schedule, make_quasi_coupon_schedule_3)
	{
		// anchor is before the "from" ("from" is on the quasi date strip)
		const auto expected = schedule{
			{ 2023y / September / 20d, 2023y / December / 20d },
			schedule::storage{
				2023y / September / 20d,
				2023y / December / 20d,
			}
		};

		const auto cds_quasi_coupon_schedule = make_quasi_coupon_schedule(
			{ 2023y / September / 20d, 2023y / December / 20d },
			Quarterly,
			June / 20d
		);

		EXPECT_EQ(expected, cds_quasi_coupon_schedule);
	}

	TEST(quasi_coupon_schedule, make_quasi_coupon_schedule_4)
	{
		// anchor is after the "from" ("from" is on the quasi date strip)
		const auto expected = schedule{
			{ 2023y / June / 20d, 2023y / December / 20d },
			schedule::storage{
				2023y / June / 20d,
				2023y / September / 20d,
				2023y / December / 20d,
			}
		};

		const auto cds_quasi_coupon_schedule = make_quasi_coupon_schedule(
			{ 2023y / June / 20d, 2023y / December / 20d },
			Quarterly,
			September / 20d
		);

		EXPECT_EQ(expected, cds_quasi_coupon_schedule);
	}

	TEST(quasi_coupon_schedule, make_quasi_coupon_schedule_5)
	{
		// anchor is after the "until" ("until" is not on the quasi date strip)
		const auto expected = schedule{
			{ 2023y / June / 7d, 2023y / December / 7d },
			schedule::storage{
				2023y / June / 7d,
				2023y / December / 7d,
			}
		};

		const auto gilt_quasi_coupon_schedule = make_quasi_coupon_schedule(
			{ 2023y / June / 7d, 2023y / December / 1d },
			SemiAnnualy,
			December / 7d
		);

		EXPECT_EQ(expected, gilt_quasi_coupon_schedule);
	}

	TEST(quasi_coupon_schedule, make_quasi_coupon_schedule_6)
	{
		// anchor is after the "until" ("until" is on the quasi date strip)
		const auto expected = schedule{
			{ 2023y / March / 20d, 2023y / June / 20d },
			schedule::storage{
				2023y / March / 20d,
				2023y / June / 20d,
			}
		};

		const auto cds_quasi_coupon_schedule = make_quasi_coupon_schedule(
			{ 2023y / March / 20d, 2023y / June / 20d },
			Quarterly,
			December / 20d
		);

		EXPECT_EQ(expected, cds_quasi_coupon_schedule);
	}

	TEST(quasi_coupon_schedule, make_quasi_coupon_schedule_7)
	{
		// anchor is before the "until" ("until" is on the quasi date strip)
		const auto expected = schedule{
			{ 2023y / March / 20d, 2023y / September / 20d },
			schedule::storage{
				2023y / March / 20d,
				2023y / June / 20d,
				2023y / September / 20d,
			}
		};

		const auto cds_quasi_coupon_schedule = make_quasi_coupon_schedule(
			{ 2023y / March / 20d, 2023y / September / 20d },
			Quarterly,
			June / 20d
		);

		EXPECT_EQ(expected, cds_quasi_coupon_schedule);
	}

}
