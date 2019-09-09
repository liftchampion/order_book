/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offers_list_price.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 09:51:20 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 09:51:20 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offers_list.h"
#include <string_view>
#include <sstream>
#include <iomanip>

using namespace std;

int			OffersList::last_digit_before_decimal_point(string_view number_str) {
	int idx = 0;

	for (auto i = number_str.rbegin(); i != number_str.rend() && *i == '0'; ++i) {
		++idx;
	}
	return idx;
}

int			OffersList::last_digit_after_decimal_point(string_view number_str) {
	int idx = PRECISION;

	for (auto i = number_str.rbegin(); i != number_str.rend() && *i == '0'; ++i) {
		--idx;
	}
	return idx;
}

double		OffersList::get_step_by_price(double price){
	stringstream ss;

	ss << fixed << setprecision(PRECISION) << price;
	string		number_str(ss.str());
	const int	decimal_point_pos =
					find(number_str.begin(), number_str.end(), '.') - number_str.begin();
	int			first_digit_after_point =
					last_digit_after_decimal_point(string_view(number_str).substr(
								  decimal_point_pos + 1));
	if (first_digit_after_point) {
		return pow(0.1, first_digit_after_point);
	}
	return pow(10,
			   last_digit_before_decimal_point(string_view(number_str).substr(
					   0, decimal_point_pos)));
}

size_t		OffersList::get_idx_by_price(double price) const{
	return static_cast<size_t>((price - offset) / step);
}

bool		OffersList::check_price_by_step(double price) const {
	double quotient = price / step;
	return (fabs(quotient - rint(quotient)) < EPSILON);
}
