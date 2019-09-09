/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offers_list_subscript.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 09:46:06 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 09:46:06 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offers_list.h"
#include <array>
#include <exception>

using namespace std;

int						OffersList::operator[](double price) const {
	const auto [can_fit, fit, present] = subscript_helper(price);

	return present ? idx_to_offer_iter[get_idx_by_price(price)]->offer.amount : 0;
}
int&					OffersList::operator[](double price){
	const auto [can_fit, fit, present] = subscript_helper(price);

	if (!present) {
		offers_list.emplace_front(price, get_step_by_price(price));
		if (!can_fit) {
			rebuild_(offers_list.begin());
		} else {
			if (!fit) {
				idx_to_offer_iter.resize(get_idx_by_price(price) + 1, offers_list.end());
			}
			idx_to_offer_iter[get_idx_by_price(price)] = offers_list.begin();
		}
	}
	return idx_to_offer_iter[get_idx_by_price(price)]->offer.amount;
}

inline array<bool, 3>	OffersList::subscript_helper(double price) const {
	if (!isfinite(price)) {
		throw domain_error("Price shouldn't be ±inf or NaN");
	}
	size_t	idx;

	bool can_fit = !need_rebuild(price);
	bool fit     = can_fit ? (idx = get_idx_by_price(price)) < idx_to_offer_iter.size() : false;
	bool present = fit ? idx_to_offer_iter[idx] != offers_list.end() : false;
	return {{can_fit, fit, present}};
}

inline bool				OffersList::need_rebuild(double price) const {
	if (offset == INIT_VAL || step == INIT_VAL) {
		return true;
	}
	if (offset - price >= EPSILON) {
		return true;
	}
	if (!check_price_by_step(price)) {
		return true;
	}
	return false;
}
