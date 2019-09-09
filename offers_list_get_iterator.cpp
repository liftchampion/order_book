/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offers_list_get_iterator.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:55:41 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 11:55:41 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offers_list.h"

using namespace std;

OffersList::iterator		OffersList::find(double price){
	const auto [can_fit, fit, present] = subscript_helper(price);
	if (!present) {
		return end();
	}
	return iterator(idx_to_offer_iter.data() + get_idx_by_price(price),
					idx_to_offer_iter.data() - 1,
					idx_to_offer_iter.data() + idx_to_offer_iter.size(),
					offers_list.end());
}

OffersList::const_iterator	OffersList::find(double price) const{
	const auto [can_fit, fit, present] = subscript_helper(price);
	if (!present) {
		return end();
	}
	return const_iterator(idx_to_offer_iter.data() + get_idx_by_price(price),
						  idx_to_offer_iter.data() - 1,
						  idx_to_offer_iter.data() + idx_to_offer_iter.size(),
						  offers_list.end());
}

OffersList::iterator		OffersList::begin(){
	lst_iter *begin_ptr = idx_to_offer_iter.data();
	lst_iter *end_ptr = begin_ptr + idx_to_offer_iter.size();

	while (begin_ptr != end_ptr && (*begin_ptr == offers_list.end() || !(*begin_ptr)->offer.amount)) {
		++begin_ptr;
	}
	return iterator(begin_ptr, begin_ptr - 1, end_ptr, offers_list.cend());
}

OffersList::const_iterator	OffersList::begin() const {
	const lst_iter *begin_ptr = idx_to_offer_iter.data();
	const lst_iter *end_ptr = begin_ptr + idx_to_offer_iter.size();

	while (begin_ptr != end_ptr && (*begin_ptr == offers_list.end() || !(*begin_ptr)->offer.amount)) {
		++begin_ptr;
	}
	return const_iterator(begin_ptr, begin_ptr - 1, end_ptr, offers_list.cend());
}

OffersList::iterator		OffersList::end(){
	return iterator(idx_to_offer_iter.data() + idx_to_offer_iter.size(),
					idx_to_offer_iter.data() - 1,
					idx_to_offer_iter.data() + idx_to_offer_iter.size(),
					offers_list.end());
}

OffersList::const_iterator	OffersList::end() const{
	return const_iterator(idx_to_offer_iter.data() + idx_to_offer_iter.size(),
						  idx_to_offer_iter.data() - 1,
						  idx_to_offer_iter.data() + idx_to_offer_iter.size(),
						  offers_list.end());
}

OffersList::reverse_iterator		OffersList::rbegin(){
	lst_iter *begin_ptr = idx_to_offer_iter.data() + idx_to_offer_iter.size() - 1;
	lst_iter *end_ptr = idx_to_offer_iter.data() - 1;

	while (begin_ptr != end_ptr && (*begin_ptr == offers_list.end() || !(*begin_ptr)->offer.amount)) {
		--begin_ptr;
	}
	return reverse_iterator(begin_ptr,
				idx_to_offer_iter.data() - 1,
				idx_to_offer_iter.data() + idx_to_offer_iter.size(),
				offers_list.cend());
}

OffersList::const_reverse_iterator	OffersList::rbegin() const {
	const lst_iter *begin_ptr = idx_to_offer_iter.data() + idx_to_offer_iter.size() - 1;
	const lst_iter *end_ptr = idx_to_offer_iter.data() - 1;

	while (begin_ptr != end_ptr && (*begin_ptr == offers_list.end() || !(*begin_ptr)->offer.amount)) {
		--begin_ptr;
	}
	return const_reverse_iterator(begin_ptr,
							idx_to_offer_iter.data() - 1,
							idx_to_offer_iter.data() + idx_to_offer_iter.size(),
							offers_list.cend());
}

OffersList::reverse_iterator		OffersList::rend(){
	return reverse_iterator(idx_to_offer_iter.data() - 1,
					idx_to_offer_iter.data() - 1,
					idx_to_offer_iter.data() + idx_to_offer_iter.size(),
					offers_list.end());
}

OffersList::const_reverse_iterator	OffersList::rend() const{
	return const_reverse_iterator(idx_to_offer_iter.data() - 1,
						  idx_to_offer_iter.data() - 1,
						  idx_to_offer_iter.data() + idx_to_offer_iter.size(),
						  offers_list.end());
}
