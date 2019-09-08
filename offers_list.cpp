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

using namespace std;

void OffersList::check_price(double price, const string& where) const {
	if (price - offset <= -numeric_limits<double>::epsilon() * offset) {
		throw domain_error(
				"Price should be greater or equal than offset (" + where + ")");
	}
	double quotient = price / step;
	if (fabs(quotient - rint(quotient)) >=
		numeric_limits<double>::epsilon() * quotient) {
		throw domain_error(
				"Price should be multiply of step (" + where + ")");
	}
}

OffersList::OffersList(double offset, double step) :
		offset(offset),
		step(step)
{}
int OffersList::operator[](double price) const {
	check_price(price, "in operator[]");
	int idx = static_cast<int>((price - offset) / step);
	if (offers.size() <= idx) {
		return 0;
	}
	return offers[idx];
}
int& OffersList::operator[](double price){
	check_price(price, "in operator[]");
	int idx = static_cast<int>((price - offset) / step);
	if (offers.size() <= idx) {
		offers.resize(idx + 1, 0);
	}
	return offers[idx];
}

OffersList::iterator OffersList::begin() {
	int	*begin_ptr = offers.data();
	int	*end = offers.data() + offers.size();

	while (begin_ptr != end && !*begin_ptr) {
		++begin_ptr;
	}
	return iterator(
			offers.data(), end, begin_ptr, offset, step);
}

OffersList::iterator OffersList::end() {
	return iterator(
			offers.data(), offers.data() + offers.size(),
			offers.data() + offers.size(), offset, step);
}

// Чтобы можно было передать offers_list по константной ссылке, необходимо реализовать
// const_iterator, реализация которого ничем не отличается от обычного кроме константности
ostream& operator<<(ostream& os, OffersList& offers_list){
	bool is_first = true;
	for (auto [price, amount] : offers_list) {
		if (!is_first) { cout << endl; }
		if (is_first) { is_first = false; }
		cout << price << " | " << amount;
	}
	return os;
}
