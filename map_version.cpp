/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_version.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:28:35 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 14:28:35 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <cmath>
#include <iostream>
#include "reverser.h"
#include "map_version.h"

using namespace std;

bool	OffersListMap::subscript_helper(double price) const {
	if (!isfinite(price)) {
		throw domain_error("Price shouldn't be ±inf or NaN");
	}
	return data.find(price) != data.end();
}

int		OffersListMap::operator[](double price) const {
	if (!subscript_helper(price)) {
		return 0;
	}
	return data.at(price);
}

int&	OffersListMap::operator[](double price) {
	subscript_helper(price);
	return data[price];
}

void	OffersListMap::rebuild() {
	for (auto it = data.begin(); it != data.end();) {
		if (!it->second) {
			it = data.erase(it);
		} else {
			++it;
		}
	}
}

ostream& operator<<(ostream& os, const OffersListMap& offers_list) {
	bool is_first = true;
	for (auto [price, amount] : reverse(offers_list.data)) {
		if (!is_first) { cout << endl; }
		if (is_first) { is_first = false; }
		cout << fixed << price << " | " << amount;
	}
	return os;
}
