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

#include <period.h>

#include <chrono>
#include <vector>
#include <memory>


namespace coupon_schedule
{

	class compounding_period // is it in the right library?
	{

	public:

		compounding_period() noexcept = delete;
		compounding_period(const compounding_period&) = default;
		compounding_period(compounding_period&&) noexcept = default;

		compounding_period(
			calendar::days_period period,
			std::chrono::year_month_day reset
		) noexcept;

		~compounding_period() noexcept = default;

		compounding_period& operator=(const compounding_period&) = default;
		compounding_period& operator=(compounding_period&&) noexcept = default;

	public:

		friend auto operator==(const compounding_period& p1, const compounding_period& p2) noexcept -> bool = default;

	public:

		// we should consider start/end here (calling into from/until) as these are more natural for this domain

//	private:
	public:

		calendar::days_period _period;

		std::chrono::year_month_day _reset;

	};



	using ccompounding_periods = std::vector<compounding_period>; // is this the right data structure?



	inline compounding_period::compounding_period(
		calendar::days_period period,
		std::chrono::year_month_day reset
	) noexcept :
		_period{ std::move(period) },
		_reset{ std::move(reset) }
	{
	}

}
