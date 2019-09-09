/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offer_list_iterator.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 03:15:59 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/08 03:15:59 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offers_list.h"

OffersList::iterator::iterator(lst_iter *ptr, lst_iter *end, lst_iter lst_end) :
		ptr(ptr), end(end), lst_end(lst_end)
{}

void					OffersList::iterator::next(){
	++ptr;
	while (ptr < end && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		++ptr;
	}
}
OffersList::iterator	OffersList::iterator::operator++() {
	next();
	return *this;
}

OffersList::iterator	OffersList::iterator::operator++(int junk) {
	iterator ret = *this;
	next();
	return ret;
}

OffersList::Offer		OffersList::iterator::operator*() const{
	return (*ptr)->offer;
}

OffersList::Offer*		OffersList::iterator::operator->() const{
	return &(*ptr)->offer;
}

bool					OffersList::iterator::operator==(const OffersList::iterator& other) const {
	return this->ptr == other.ptr;
}

bool					OffersList::iterator::operator!=(const OffersList::iterator& other) const {
	return this->ptr != other.ptr;
}
