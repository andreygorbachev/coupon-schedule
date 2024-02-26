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

#include <date_adjuster.h>
#include <quasi_coupon_schedule.h> // for SemiAnnualy etc

#include <schedule.h>

#include <gtest/gtest.h>

#include <chrono>
#include <stdexcept>

using namespace gregorian;

using namespace std;
using namespace std::chrono;


namespace coupon_schedule
{

	TEST(not_after_quasi_coupon_date, adjust) // I wonder if we have "<=" "<" and ">=" ">" here is some sense
	{
		// anchor is on the "date" ("date" is on the quasi date strip)
		EXPECT_EQ(2022y / December / 7d, NotAfter.adjust(2022y / December / 7d, 2022y / December / 7d, SemiAnnualy)); // should anchor and frequency order be the same as in QCS?

		// anchor is before the "date" ("date" is not on the quasi date strip)
		EXPECT_EQ(2022y / December / 7d, NotAfter.adjust(2023y / January / 1d, 2022y / December / 7d, SemiAnnualy));

		// anchor is before the "date" ("date" is on the quasi date strip)
		EXPECT_EQ(2022y / December / 7d, NotAfter.adjust(2022y / December / 7d, 2022y / June / 7d, SemiAnnualy));
	}


	TEST(not_before_quasi_coupon_date, adjust)
	{
		// anchor is on the "date" ("date" is on the quasi date strip)
		EXPECT_EQ(2022y / December / 7d, NotBefore.adjust(2022y / December / 7d, 2022y / December / 7d, SemiAnnualy));

		// anchor is after the "date" ("date" is not on the quasi date strip)
		EXPECT_EQ(2022y / December / 7d, NotBefore.adjust(2023y / June / 1d, 2023y / June / 7d, SemiAnnualy));

		// anchor is after the "date" ("date" is on the quasi date strip)
		EXPECT_EQ(2022y / December / 7d, NotBefore.adjust(2022y / December / 7d, 2023y / June / 7d, SemiAnnualy));
	}

}
