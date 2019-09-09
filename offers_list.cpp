/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offers_list.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 03:11:19 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/08 03:11:19 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include "offers_list.h"
#include <sstream>
#include <string_view>
#include <iomanip>

using namespace std;

int OffersList::last_digit_before_decimal_point(string_view number_str) {
	int idx = 0;

	for (auto i = number_str.rbegin(); i != number_str.rend() && *i == '0'; ++i) {
		++idx;
	}
	return idx;
}

int OffersList::first_digit_after_decimal_point(string_view number_str) {
	int idx = PRECISION;

	for (auto i = number_str.rbegin(); i != number_str.rend() && *i == '0'; ++i) {
		--idx;
	}
	return idx;
}

double OffersList::get_step_by_price(double price){
	stringstream ss;

	ss << fixed << setprecision(PRECISION) << price;
	string		number_str(ss.str());
	const int	decimal_point_pos =
			find(number_str.begin(), number_str.end(), '.') - number_str.begin();
	int			first_digit_after_point =
			first_digit_after_decimal_point(string_view(number_str).substr(decimal_point_pos + 1));
	if (first_digit_after_point) {
		return pow(0.1, first_digit_after_point);
	}
	return pow(10, last_digit_before_decimal_point(string_view(number_str).substr(0, decimal_point_pos)));
}

void OffersList::check_and_rebuild_if_needed(double price){
	if (!isfinite(price)) {
		throw domain_error("Price shouldn't be ±inf or NaN");
	}
	if (offset == INIT_VAL || step == INIT_VAL) {
		offset = price;
	}
//	if (price - offset <= -numeric_limits<double>::epsilon() * offset) {
//		throw domain_error(
//				"Price should be greater or equal than offset (" + where + ")");
//	}
//	double quotient = price / step;
//	if (fabs(quotient - rint(quotient)) >=
//		numeric_limits<double>::epsilon() * quotient) {
//		throw domain_error(
//				"Price should be multiply of step (" + where + ")");
//	}
}

//int OffersList::operator[](double price) const {
//	check_and_rebuild_if_needed(price, "in operator[]");
//	int idx = static_cast<int>((price - offset) / step);
//	if (idx_to_offer_iter.size() <= idx) {
//		return 0;
//	}
//	return idx_to_offer_iter[idx];
//}
int& OffersList::operator[](double price){
	check_and_rebuild_if_needed(price);
	int idx = static_cast<int>((price - offset) / step);
	if (idx_to_offer_iter.size() <= idx) {
		idx_to_offer_iter.resize(idx + 1, 0);
	}
	return idx_to_offer_iter[idx];
}

//OffersList::iterator OffersList::begin() {
//	int	*begin_ptr = idx_to_offer_iter.data();
//	int	*end = idx_to_offer_iter.data() + idx_to_offer_iter.size();
//
//	while (begin_ptr != end && !*begin_ptr) {
//		++begin_ptr;
//	}
//	return iterator(
//			idx_to_offer_iter.data(), end, begin_ptr, offset, step);
//}
//
//OffersList::iterator OffersList::end() {
//	return iterator(
//			idx_to_offer_iter.data(), idx_to_offer_iter.data() + idx_to_offer_iter.size(),
//			idx_to_offer_iter.data() + idx_to_offer_iter.size(), offset, step);
//}

// Чтобы можно было передать offers_list по константной ссылке, необходимо реализовать
// const_iterator, реализация которого ничем не отличается от обычного кроме константности
//ostream& operator<<(ostream& os, OffersList& offers_list){
//	bool is_first = true;
//	for (auto [price, amount] : offers_list) {
//		if (!is_first) { cout << endl; }
//		if (is_first) { is_first = false; }
//		cout << price << " | " << amount;
//	}
//	return os;
//}
