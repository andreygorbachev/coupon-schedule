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

#include <coupon_period.h>

#include <period.h>

#include <gtest/gtest.h>

#include <chrono>


using namespace gregorian;
using namespace std::chrono;


namespace coupon_schedule
{

	TEST(coupon_period, constructor1)
	{
		const auto p = coupon_period{
			{ 2023y / January / 1d, 2023y / June / 7d },
			2023y / June / 7d,
			2023y / June / 1d
		};

		EXPECT_EQ(2023y / January / 1d, p._period.get_from());
		EXPECT_EQ(2023y / June / 7d, p._period.get_until());
		EXPECT_EQ(2023y / June / 7d, p._pay);
		EXPECT_EQ(2023y / June / 1d, p._ex_div);
	}

	TEST(coupon_period, constructor2)
	{
		const auto p = coupon_period{
			{ 2023y / January / 1d, 2023y / June / 7d },
			2023y / June / 7d
		};

		EXPECT_EQ(2023y / January / 1d, p._period.get_from());
		EXPECT_EQ(2023y / June / 7d, p._period.get_until());
		EXPECT_EQ(2023y / June / 7d, p._pay);
		EXPECT_EQ(2023y / June / 7d, p._ex_div);
	}

	TEST(coupon_period, constructor3)
	{
		const auto s = schedule{
			{ 2023y / January / 1d, 2023y / June / 31d },
			{
				2023y / January / 1d,
				2023y / June / 7d,
			}
		};

		const auto c = calendar{
			NoWeekend,
			s
		};

		const auto p = coupon_period{
			{ 2023y / January / 1d, 2023y / June / 7d },
			c
		};

		EXPECT_EQ(2023y / January / 1d, p._period.get_from());
		EXPECT_EQ(2023y / June / 7d, p._period.get_until());
		EXPECT_EQ(2023y / June / 8d, p._pay);
		EXPECT_EQ(2023y / June / 7d, p._ex_div);
	}

}
