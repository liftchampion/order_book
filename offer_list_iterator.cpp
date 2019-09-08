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
	if (_offer_ptr != nullptr) { delete(_offer_ptr); }
	_offer_ptr = nullptr;
}

OffersList::iterator OffersList::iterator::operator++() {
	++ptr;
	while (ptr < end && !*ptr) {
		++ptr;
	}
	return OffersList::iterator(
			this->begin, this->end, this->ptr, this->offset, this->step);
}

OffersList::iterator OffersList::iterator::operator++(int junk) {
	iterator iter = OffersList::iterator(
			this->begin, this->end, this->ptr, this->offset, this->step);
	++ptr;
	while (ptr < end && !*ptr) {
		++ptr;
	}
	return iter;
}

OffersList::Offer<int&> OffersList::iterator::operator*() {
	int distance = static_cast<int>(ptr - begin);
	return {distance * step + offset, *ptr};
}

OffersList::Offer<int&>* OffersList::iterator::operator->() {
	int distance = static_cast<int>(ptr - begin);

	if (_offer_ptr != nullptr) { delete(_offer_ptr); }
	_offer_ptr = new Offer<int&>(distance * step + offset, *ptr);
	return _offer_ptr;
}
