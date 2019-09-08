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
#include <utility>
#include <cmath>
#include <limits>
#include "offers_list.h"

using namespace std;

void OffersList::check_price(double price, const string& where) const {
	if (price - offset <= -numeric_limits<double>::epsilon()) {
		throw domain_error(
				"Price should be greater or equal than offset (" + where + ")");
	}
	double quotient = price / step;
	if (fabs(quotient - static_cast<int>(quotient)) >=
		numeric_limits<double>::epsilon()) {
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
	return iterator(offers.data(), offers.data() + offers.size(), offers.data(), offset, step);
}

const vector<int>& OffersList::get_offers() const{
	return offers;
}
double OffersList::get_offset() const{
	return offset;
}
double OffersList::get_step() const{
	return step;
}

ostream& operator<<(ostream& os, const OffersList& order_book){
	double step = order_book.get_step();
	double offset = order_book.get_offset();
	const auto& offers = order_book.get_offers();
	for (size_t i = 0; i < offers.size(); ++i) {
		cout << offset + step * i << " | " << offers[i] << endl;
	}
	return os;
}