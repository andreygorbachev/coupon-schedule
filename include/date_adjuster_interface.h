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

#include "duration_variant.h"

#include <chrono>


namespace coupon_schedule
{

	class date_adjuster // very similar to business_day_convention - possibly bring them together? (business_day_convention derived from date_adjuster?)
	{

	public:

		date_adjuster() noexcept = default;
		virtual ~date_adjuster() noexcept = default;

		date_adjuster(const date_adjuster&) = delete;
		date_adjuster(date_adjuster&&) noexcept = delete;

		date_adjuster& operator=(const date_adjuster&) = delete;
		date_adjuster& operator=(date_adjuster&&) noexcept = delete;

	public:

		auto adjust(
			const std::chrono::year_month_day& ymd,
			const duration_variant& frequency,
			const std::chrono::year_month_day& anchor
		) const -> std::chrono::year_month_day; // can we make this noexcept?

	private:

		virtual auto _adjust(
			const std::chrono::year_month_day& ymd,
			const duration_variant& frequency,
			const std::chrono::year_month_day& anchor
		) const -> std::chrono::year_month_day = 0;

	};



	inline auto date_adjuster::adjust(
		const std::chrono::year_month_day& ymd,
		const duration_variant& frequency,
		const std::chrono::year_month_day& anchor
	) const -> std::chrono::year_month_day
	{
		return _adjust(ymd, frequency, anchor);
	}

}
