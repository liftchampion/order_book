/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 04:14:44 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 04:14:44 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "offers_list.h"

using namespace std;

OffersList::Offer::Offer(double price) : price(price)
{}

OffersList::OfferData::OfferData(double price, double step) :
	offer(price),
	step(step)
{}
