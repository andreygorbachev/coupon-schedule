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
#include <vector>
#include <memory>


namespace coupon_schedule
{

	// should there be a notion of a calendar::period of just 2 dates?
	// (and here it could be extended to coupon_period by addition of a pay date?)
	class period
	{

	public:

		period() noexcept = delete;
		period(const period&) = default;
		period(period&&) noexcept = default;

		period(
			std::chrono::year_month_day start,
			std::chrono::year_month_day end,
			std::chrono::year_month_day pay
		) noexcept;

		~period() noexcept = default;

		period& operator=(const period&) = default;
		period& operator=(period&&) noexcept = default;

	public:

		friend auto operator==(const period& p1, const period& p2) noexcept -> bool = default;

//	private:
	public:

		std::chrono::year_month_day _start;
		std::chrono::year_month_day _end;

		std::chrono::year_month_day _pay;

		// invariant to consider: _start <= _end (could be the same day for 1 day trades)
		// _pay is usually >= _end, but I am not sure it is guranteed
	};



	using periods = std::vector<period>; // is this the right data structure?



	inline period::period(
		std::chrono::year_month_day start,
		std::chrono::year_month_day end,
		std::chrono::year_month_day pay
	) noexcept :
		_start{ std::move(start) },
		_end{ std::move(end) },
		_pay{ std::move(pay) }
	{
	}

}
