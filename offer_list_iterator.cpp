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

OffersList::iterator::iterator(int *begin, int *end, int *ptr, double offset, double step):
		begin(begin), end(end), ptr(ptr), offset(offset), step(step)
{}

OffersList::iterator::~iterator() {
	delete(_offer_ptr);
}

OffersList::iterator OffersList::iterator::operator++() {
	iterator iter = *this;
	while (ptr != end && !*ptr) {
		++ptr;
	}
	return iter;
}

OffersList::iterator OffersList::iterator::operator++(int junk) {
	while (ptr != end && !*ptr) {
		++ptr;
	}
	return *this;
}

OffersList::Offer<int&> OffersList::iterator::operator*() {
	int distance = static_cast<int>(ptr - begin);
	return {distance * step + offset, *ptr};
}

OffersList::Offer<int&>* OffersList::iterator::operator->() {
	int distance = static_cast<int>(ptr - begin);

	_offer_ptr = new Offer<int&>(distance * step + offset, *ptr);

	//_offer.price = distance * step + offset;
	//_offer.amount = *ptr;
	return _offer_ptr;
}
