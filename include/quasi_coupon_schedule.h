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
#include "date_adjuster.h"

#include <schedule.h>

#include <chrono>
#include <memory>
#include <cassert>

#include <ranges>
#include <iterator>
#include <concepts>
#include <algorithm>
#include <memory>
#include <stdexcept>


namespace coupon_schedule
{

	// where should we consider schedules running on month end?

	// probably not the right place for these
    constexpr auto Annualy = duration_variant{ std::chrono::years{ 1 } };
    constexpr auto SemiAnnualy = duration_variant{ std::chrono::months{ 6 } };
	constexpr auto Quarterly = duration_variant{ std::chrono::months{ 3 } };
	constexpr auto Monthly = duration_variant{ std::chrono::months{ 1 } };
    constexpr auto Weekly = duration_variant{ std::chrono::weeks{ 1 } };
    constexpr auto Daily = duration_variant{ std::chrono::days{ 1 } };


	inline auto _increase_ymd_as_needed(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day& issue,
		const duration_variant& frequency
	) -> std::chrono::year_month_day
	{
		while (advance(d, frequency) <= issue)
			d = advance(d, frequency);

		return d;
	}

	inline auto _decrease_ymd_as_needed(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day& issue,
		const duration_variant& frequency
	) -> std::chrono::year_month_day
	{
		while (d > issue)
			d = retreat(d, frequency);

		return d;
	}

	inline auto _make_quasi_coupon_schedule_storage(
		std::chrono::year_month_day d,
		const std::chrono::year_month_day& maturity,
		const duration_variant& frequency
	) -> gregorian::schedule::storage
	{
		auto s = gregorian::schedule::storage{};

		while (s.insert(d), d < maturity)
			d = advance(d, frequency);

		return s;
	}


	inline auto make_quasi_coupon_schedule(
		const gregorian::days_period& issue_maturity,
		const duration_variant& frequency,
		const std::chrono::year_month_day& anchor
	) -> gregorian::schedule
	{
		const auto& issue = issue_maturity.get_from();
		const auto& maturity = issue_maturity.get_until();

		auto a = anchor;

		if (a < issue)
			a = _increase_ymd_as_needed(a, issue, frequency);
		else if (a > issue)
			a = _decrease_ymd_as_needed(a, issue, frequency);
		else
			; // if a == issue no need to do anything more

		auto s = _make_quasi_coupon_schedule_storage(a, maturity, frequency);

        assert(!s.empty());
		auto p = gregorian::period{ *s.cbegin(), *s.crbegin() };

		return gregorian::schedule{	std::move(p), std::move(s) };
	}



	namespace experimental
	{

        class quasi_coupon_schedule_view : public std::ranges::view_interface<quasi_coupon_schedule_view>
        {

        public:

            class iterator
            {

            public:

                using iterator_category = std::input_iterator_tag; // or should we allow to move in both directions?
                using value_type = std::chrono::year_month_day;
                using difference_type = int; // is this correct?
                using reference = value_type;

            private:

                value_type ymd_;
                duration_variant frequency_;

            public:

                explicit iterator(
                    value_type ymd,
                    duration_variant frequency
                ) : ymd_{ std::move(ymd) },
                    frequency_{ std::move(frequency) }
                {
                }

                auto operator++() -> iterator&
                {
                    ymd_ = advance(ymd_, frequency_);
                    return *this;
                }

                auto operator++(int) -> iterator
                {
                    auto retval = *this;
                    ++(*this);
                    return retval;
                }

                friend auto operator==(const iterator& x, const iterator& y) -> bool
                {
                    return *x == *y;
                }

                auto operator*() const -> value_type
                {
                    return ymd_;
                }

            };

        private:

            iterator begin_;

        public:

            explicit quasi_coupon_schedule_view(
                std::chrono::year_month_day anchor,
                duration_variant frequency
            ) : begin_{ iterator{ std::move(anchor), std::move(frequency) } }
            {
            }

            auto begin() const
            {
                return begin_;
            }

            auto end() const
            {
                return std::unreachable_sentinel;
            }

        };


        inline auto _adjust_anchor(
            const gregorian::days_period& issue_maturity,
            const duration_variant& frequency,
            const std::chrono::year_month_day& anchor
        ) -> std::chrono::year_month_day
        {
            assert(is_forward(frequency) || is_backward(frequency));
                
            const auto& issue = issue_maturity.get_from();
            const auto& maturity = issue_maturity.get_until();

            if (is_forward(frequency))
                if (anchor <= issue) // should we explicitly handle "==" case? (no adjustment needed)
                    return NotAfter.adjust(issue, frequency, anchor);
                else
                    return NotBefore.adjust(issue, frequency, anchor);
            else
                if (anchor >= maturity)
                    return NotAfter.adjust(maturity, frequency, anchor);
                else
                    return NotBefore.adjust(maturity, frequency, anchor);
        }


        inline auto _make_quasi_coupon_schedule_forward(
            const gregorian::days_period& issue_maturity,
            const duration_variant& frequency,
            const std::chrono::year_month_day& anchor
        ) -> auto
        {
            assert(is_forward(frequency));

            const auto& issue = issue_maturity.get_from();
            const auto& maturity = issue_maturity.get_until();
            assert(anchor <= issue);

            const auto is_not_past_just_after = [&](const auto d) // are these "business day conventions"? (but we should call them something differently?)
            {
                return retreat(d, frequency) < maturity;
            };

            return
                quasi_coupon_schedule_view{ anchor, frequency } |
                std::views::take_while(is_not_past_just_after);
        }


        inline auto _make_quasi_coupon_schedule_backward(
            const gregorian::days_period& issue_maturity,
            const duration_variant& frequency,
            const std::chrono::year_month_day& anchor
        ) -> auto
        {
            assert(is_backward(frequency));

            const auto& issue = issue_maturity.get_from();
            const auto& maturity = issue_maturity.get_until();
            assert(anchor >= maturity);

            const auto is_not_past_just_after = [&](const auto d)
            {
                return retreat(d, frequency) > issue;
            };

            return
                quasi_coupon_schedule_view{ anchor, frequency } |
                std::views::take_while(is_not_past_just_after);
        }


        // should we combine frequency and anchor into a single structure? (as for quasi-coupon schedule they will always go together)
        // derive from schedule?
        inline auto make_quasi_coupon_schedule(
            const gregorian::days_period& issue_maturity,
            const duration_variant& frequency,
            const std::chrono::year_month_day& anchor
        ) -> gregorian::schedule
        {
            if (!is_forward(frequency) && !is_backward(frequency))
                throw std::out_of_range{ "Empty frequency does not work for quasi coupon schedule" }; // or shold we do something else, like return some type of empty schedule

            const auto adjusted_anchor = _adjust_anchor(issue_maturity, frequency, anchor);

            auto s = is_forward(frequency) ?
                _make_quasi_coupon_schedule_forward(issue_maturity, frequency, adjusted_anchor) |
                std::ranges::to<gregorian::schedule::storage>()
            :
                _make_quasi_coupon_schedule_backward(issue_maturity, frequency, adjusted_anchor) |
                std::ranges::to<gregorian::schedule::storage>(); // do we need to reverse it?
            // can we have "to" directly to gregorian::schedule?

            assert(!s.empty());
            auto p = gregorian::period{ *s.cbegin(), *s.crbegin() };

            return gregorian::schedule{ std::move(p), std::move(s) };
        }

    }



    inline auto make_quasi_coupon_schedule(
        const gregorian::days_period& issue_maturity,
        const duration_variant& frequency, // at the moment we are not thinking about tricky situations towards the end of month
        const std::chrono::month_day& anchor
    ) -> gregorian::schedule
    {
        const auto a = issue_maturity.get_from().year() / anchor; // this would only work for situations where frequency is less that a year - how should we check for that?
        // are we ok to make adjustment first and then fill a shedule generation as a second step?
        // (if anchor is after the issue we can adjust a generate the bit prior to the anchor at the same time, but then we'll have to combine this with the part above the anchor)

        return experimental::make_quasi_coupon_schedule(issue_maturity, frequency, a);
    }

}
