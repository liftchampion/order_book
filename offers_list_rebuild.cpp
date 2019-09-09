/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offers_list_rebuild.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 09:48:19 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 09:48:19 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offers_list_class.h"

using namespace std;

void					OffersList::rebuild() {
	rebuild_(offers_list.end());
}

void 					OffersList::rebuild_(lst_iter no_del_if_empty) {
	const auto [new_offset, new_step] = find_min_step_offset_and_rm_empty(no_del_if_empty);
	idx_to_offer_iter.clear();
	if (offers_list.empty()) {
		offset = INIT_VAL;
		step   = INIT_VAL;
		return;
	}
	offset = new_offset;
	step   = new_step;
	size_t idx;
	for (auto offer_it = offers_list.begin(); offer_it != offers_list.end(); ++offer_it ) {
		if ((idx = get_idx_by_price(offer_it->offer.price)) >= idx_to_offer_iter.size()) {
			idx_to_offer_iter.resize(idx + 1, offers_list.end());
		}
		idx_to_offer_iter[idx] = offer_it;
	}
}

pair<double, double>	OffersList::find_min_step_offset_and_rm_empty(lst_iter no_del_iter) {
	double		min_offset = numeric_limits<double>::infinity();
	double		min_step   = numeric_limits<double>::infinity();
	lst_iter	curr_it;

	for (auto it = offers_list.before_begin(); next(it) != offers_list.end();) {
		if ((curr_it = next(it)) != no_del_iter && curr_it->offer.amount == 0) {
			offers_list.erase_after(it);
		} else {
			if (min_offset > curr_it->offer.price) { min_offset = curr_it->offer.price; }
			if (min_step   > curr_it->step ) { min_step = curr_it->step; }
			++it;
		}
	}
	return make_pair(min_offset, min_step);
}
