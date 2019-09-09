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

int OffersList::last_digit_after_decimal_point(string_view number_str) {
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
					last_digit_after_decimal_point(string_view(number_str).substr(
											   decimal_point_pos + 1));
	if (first_digit_after_point) {
		return pow(0.1, first_digit_after_point);
	}
	return pow(10,
			last_digit_before_decimal_point(string_view(number_str).substr(
										0, decimal_point_pos)));
}

inline size_t OffersList::get_idx_by_price(double price) const{
	return static_cast<size_t>((price - offset) / step);
}

pair<double, double> OffersList::find_min_step_offset_and_rm_empty(lst_iter no_del_iter) {
	double		min_offset = numeric_limits<double>::infinity();
	double		min_step   = numeric_limits<double>::infinity();
	lst_iter	curr_it;

	for (auto it = offers_list.before_begin(); next(it) != offers_list.end();) {
		if ((curr_it = next(it)) != no_del_iter && curr_it->amount == 0) {
			offers_list.erase_after(it);
		} else {
			if (min_offset > curr_it->price) { min_offset = curr_it->price; }
			if (min_step   > curr_it->step ) { min_step   = curr_it->step; }
			++it;
		}
	}
	return make_pair(min_offset, min_step);
}

void OffersList::rebuild_(lst_iter no_del_if_empty) {
	const auto new_offset_step = find_min_step_offset_and_rm_empty(no_del_if_empty);
	if (offers_list.empty()) {
		offset = INIT_VAL;
		step   = INIT_VAL;
		return;
	}
	offset = new_offset_step.first;
	step   = new_offset_step.second;
	int idx;
	idx_to_offer_iter.clear();
	for (auto offer_it = offers_list.begin(); offer_it != offers_list.end(); ++offer_it ) {
		if ((idx = get_idx_by_price(offer_it->price)) >= idx_to_offer_iter.size()) {
			idx_to_offer_iter.resize(idx + 1, offers_list.end());
		}
		idx_to_offer_iter[idx] = offer_it;
	}
}

inline bool OffersList::check_price_by_step(double price) const {
	double quotient = price / step;
	return (fabs(quotient - rint(quotient)) < EPSILON);
}

inline bool		OffersList::need_rebuild(double price) const {

	if (offset != INIT_VAL && offset - price >= EPSILON) {
		return true;
	}
	if (step != INIT_VAL && !check_price_by_step(price)) {
		return true;
	}
	return false;
}

inline void OffersList::subscript_helper(double price, bool& can_fit, bool& present) const {
	if (!isfinite(price)) {
		throw domain_error("Price shouldn't be ±inf or NaN");
	}
	int	 idx;
	bool fit;

	can_fit = !need_rebuild(price);
	fit     = can_fit ? (idx = get_idx_by_price(price)) < idx_to_offer_iter.size() : false;
	present = fit ? idx_to_offer_iter[idx] != offers_list.end() : false;
}

int OffersList::operator[](double price) const {
	bool can_fit;
	bool present;

	subscript_helper(price, can_fit, present);

	return present ? idx_to_offer_iter[get_idx_by_price(price)]->amount : 0;
}
int& OffersList::operator[](double price){
	bool can_fit;
	bool present;

	subscript_helper(price, can_fit, present);
	if (!present) {
		offers_list.emplace_front(price, get_step_by_price(price));
		if (!can_fit) {
			rebuild_(offers_list.begin());
		}
	}
	return idx_to_offer_iter[get_idx_by_price(price)]->amount;
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
