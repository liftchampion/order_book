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

using namespace std;

#include "offers_list.h"

OffersList::Offer::Offer(double price, double step) :
	price(price),
	step(step)
{}
