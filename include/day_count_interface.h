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

#include <chrono>


namespace coupon_schedule
{

	class day_count
	{

	public:

		virtual ~day_count() noexcept = default;

	public:

		auto fraction(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> double; // noexcept?
		// return a ratio?

	private:

		virtual auto _numerator(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> int = 0; // noexcept?
		virtual auto _denominator() const noexcept -> int = 0;
		// correct return types?

	};



	// should we have a function which takes a period and a day count and returns a fraction?



	inline auto day_count::fraction(const std::chrono::year_month_day& start, const std::chrono::year_month_day& end) const -> double
	{
		// what is start > end?

		return static_cast<double>(_numerator(start, end)) / static_cast<double>(_denominator());
	}

}
