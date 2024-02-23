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

#include <duration_variant.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace coupon_schedule
{

	TEST(duration_variant, advance)
	{
		EXPECT_EQ(2024y / January / 2d, advance(2024y / January / 1d, days{ 1 }));
		EXPECT_EQ(2024y / January / 8d, advance(2024y / January / 1d, weeks{ 1 }));
		EXPECT_EQ(2024y / February / 1d, advance(2024y / January / 1d, months{ 1 }));
		EXPECT_EQ(2025y / January / 1d, advance(2024y / January / 1d, years{ 1 }));
	}

	TEST(duration_variant, retreat)
	{
		EXPECT_EQ(2023y / December / 31d, retreat(2024y / January / 1d, days{ 1 }));
		EXPECT_EQ(2023y / December / 25d, retreat(2024y / January / 1d, weeks{ 1 }));
		EXPECT_EQ(2023y / December / 1d, retreat(2024y / January / 1d, months{ 1 }));
		EXPECT_EQ(2023y / January / 1d, retreat(2024y / January / 1d, years{ 1 }));
	}

}
