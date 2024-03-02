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
#include <stdexcept>


namespace coupon_schedule
{

	class day_count
	{

	public:

		day_count() noexcept = default;
		virtual ~day_count() noexcept = default;

		day_count(const day_count&) = delete;
		day_count(day_count&&) noexcept = delete;

		day_count& operator=(const day_count&) = delete;
		day_count& operator=(day_count&&) noexcept = delete;

	public:

		auto fraction(const gregorian::days_period& period) const -> double; // noexcept?

	private:

		virtual auto _fraction(const gregorian::days_period& period) const -> double = 0; // noexcept?

	};



	inline auto day_count::fraction(const gregorian::days_period& period) const -> double
	{
		return _fraction(period);
	}

}
