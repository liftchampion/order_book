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

#include "offers_list_class.h"
#include "offers_list_iterators.h"

OffersList::iterator::iterator(lst_iter *ptr,
							   const lst_iter *before_begin,
							   const lst_iter *end,
							   c_lst_iter lst_end) :
		ptr(ptr), before_begin(before_begin), end(end), lst_end(lst_end)
{}

void					OffersList::iterator::next(){
	++ptr;
	while (ptr < end && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		++ptr;
	}
}

void					OffersList::iterator::prev(){
	--ptr;
	while (ptr > before_begin && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		--ptr;
	}
}

OffersList::iterator	OffersList::iterator::operator++() {
	next();
	return *this;
}

OffersList::iterator	OffersList::iterator::operator++(int junk) {
	junk = 0;
	iterator ret = *this;
	next();
	return ret;
}

OffersList::iterator	OffersList::iterator::operator--() {
	prev();
	return *this;
}

OffersList::iterator	OffersList::iterator::operator--(int junk) {
	junk = 0;
	iterator ret = *this;
	prev();
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

////////////////////////////////////////////////////////////////////////////////

OffersList::const_iterator::const_iterator(const lst_iter *ptr,
										   const lst_iter *before_begin,
										   const lst_iter *end,
										   c_lst_iter lst_end) :
		ptr(ptr), before_begin(before_begin), end(end), lst_end(lst_end)
{}

void						OffersList::const_iterator::next(){
	++ptr;
	while (ptr < end && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		++ptr;
	}
}

void						OffersList::const_iterator::prev(){
	--ptr;
	while (ptr > before_begin && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		--ptr;
	}
}

OffersList::const_iterator	OffersList::const_iterator::operator++() {
	next();
	return *this;
}

OffersList::const_iterator	OffersList::const_iterator::operator++(int junk) {
	junk = 0;
	const_iterator ret = *this;
	next();
	return ret;
}

OffersList::const_iterator	OffersList::const_iterator::operator--() {
	prev();
	return *this;
}

OffersList::const_iterator	OffersList::const_iterator::operator--(int junk) {
	junk = 0;
	const_iterator ret = *this;
	prev();
	return ret;
}

OffersList::Offer			OffersList::const_iterator::operator*() const{
	return (*ptr)->offer;
}

OffersList::Offer*			OffersList::const_iterator::operator->() const{
	return &(*ptr)->offer;
}

bool						OffersList::const_iterator::operator==(
								const OffersList::const_iterator& other) const {
	return this->ptr == other.ptr;
}

bool						OffersList::const_iterator::operator!=(
								const OffersList::const_iterator& other) const {
	return this->ptr != other.ptr;
}

////////////////////////////////////////////////////////////////////////////////

OffersList::reverse_iterator::reverse_iterator(lst_iter *ptr,
											   const lst_iter *before_begin,
											   const lst_iter *end,
											   c_lst_iter lst_end) :
		ptr(ptr), before_begin(before_begin), end(end), lst_end(lst_end)
{}

void							OffersList::reverse_iterator::next(){
	++ptr;
	while (ptr < end && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		++ptr;
	}
}

void							OffersList::reverse_iterator::prev(){
	--ptr;
	while (ptr > before_begin && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		--ptr;
	}
}

OffersList::reverse_iterator	OffersList::reverse_iterator::operator++() {
	prev();
	return *this;
}

OffersList::reverse_iterator	OffersList::reverse_iterator::operator++(int junk) {
	junk = 0;
	reverse_iterator ret = *this;
	prev();
	return ret;
}

OffersList::reverse_iterator	OffersList::reverse_iterator::operator--() {
	next();
	return *this;
}

OffersList::reverse_iterator	OffersList::reverse_iterator::operator--(int junk) {
	junk = 0;
	reverse_iterator ret = *this;
	next();
	return ret;
}

OffersList::Offer				OffersList::reverse_iterator::operator*() const{
	return (*ptr)->offer;
}

OffersList::Offer*				OffersList::reverse_iterator::operator->() const{
	return &(*ptr)->offer;
}

bool							OffersList::reverse_iterator::operator==(
									const OffersList::reverse_iterator& other) const {
	return this->ptr == other.ptr;
}

bool							OffersList::reverse_iterator::operator!=(
									const OffersList::reverse_iterator& other) const {
	return this->ptr != other.ptr;
}

////////////////////////////////////////////////////////////////////////////////

OffersList::const_reverse_iterator::const_reverse_iterator(const lst_iter *ptr,
											   			   const lst_iter *before_begin,
											   			   const lst_iter *end,
											   			   c_lst_iter lst_end) :
		ptr(ptr), before_begin(before_begin), end(end), lst_end(lst_end)
{}

void								OffersList::const_reverse_iterator::next(){
	++ptr;
	while (ptr < end && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		++ptr;
	}
}

void								OffersList::const_reverse_iterator::prev(){
	--ptr;
	while (ptr > before_begin && (*ptr == lst_end || !(*ptr)->offer.amount)) {
		--ptr;
	}
}

OffersList::const_reverse_iterator	OffersList::const_reverse_iterator::operator++() {
	prev();
	return *this;
}

OffersList::const_reverse_iterator	OffersList::const_reverse_iterator::operator++(int junk) {
	junk = 0;
	const_reverse_iterator ret = *this;
	prev();
	return ret;
}

OffersList::const_reverse_iterator	OffersList::const_reverse_iterator::operator--() {
	next();
	return *this;
}

OffersList::const_reverse_iterator	OffersList::const_reverse_iterator::operator--(int junk) {
	junk = 0;
	const_reverse_iterator ret = *this;
	next();
	return ret;
}

OffersList::Offer				OffersList::const_reverse_iterator::operator*() const{
	return (*ptr)->offer;
}

OffersList::Offer*				OffersList::const_reverse_iterator::operator->() const{
	return &(*ptr)->offer;
}

bool							OffersList::const_reverse_iterator::operator==(
									const OffersList::const_reverse_iterator& other) const {
	return this->ptr == other.ptr;
}

bool							OffersList::const_reverse_iterator::operator!=(
									const OffersList::const_reverse_iterator& other) const {
	return this->ptr != other.ptr;
}
