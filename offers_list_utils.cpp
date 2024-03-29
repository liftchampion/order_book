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
#include <iomanip>
#include "offers_list_class.h"
#include "offers_list_iterators.h"
#include "reverser.h"

using namespace std;

bool 		OffersList::set_offset(double new_offset) {
	if (offset != INIT_VAL) {
		return false;
	}
	offset = new_offset;
	return true;
}

bool 		OffersList::set_step(double new_step) {
	if (step != INIT_VAL) {
		return false;
	}
	step = new_step;
	return true;
}

double 		OffersList::get_step() const{
	return step;
}

bool		OffersList::empty() const {
	return idx_to_offer_iter.empty();
}

void		OffersList::clear() {
	idx_to_offer_iter.clear();
	offers_list.clear();
	offset = INIT_VAL;
	step = INIT_VAL;
}

void		OffersList::shrink_to_fit() {
	rebuild();
	idx_to_offer_iter.shrink_to_fit();
}

// Чтобы можно было передать offers_list по константной ссылке, необходимо реализовать
// const_iterator, реализация которого ничем не отличается от обычного кроме константности
ostream&					operator<<(ostream& os, const OffersList& offers_list){
	bool is_first = true;
	for (auto [price, amount] : reverse(offers_list)) {
		if (!is_first) { cout << endl; }
		if (is_first) { is_first = false; }
		int prec = static_cast<int>(lround(-log10(offers_list.get_step())));
		prec = prec >= 0 ? prec : 0;
		cout << fixed << setprecision(prec) << price << " | " << amount;
	}
	return os;
}
