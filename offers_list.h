/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offers_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 03:06:48 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/08 03:06:48 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>
#include <iostream>

class OffersList {
private:
	void check_price(double price, const std::string& where) const;
public:

	template <typename A>
	class Offer {
	public:
		Offer(double price, A amount) : price(price), amount(amount) {}
		double	price = 0;
		A		amount;
	};

	class iterator : public std::iterator<std::bidirectional_iterator_tag, const Offer<int&>>
	{
	public:
		iterator(int *begin, int *end, int *ptr, double offset, double step);
		~iterator();
		iterator operator++();
		iterator operator++(int junk);
		Offer<int&> operator*();
		Offer<int&>* operator->();
	private:
		int 		*begin;
		int 		*end;
		int			*ptr;
		double		offset;
		double		step;
		Offer<int&>	*_offer_ptr = nullptr;
	};


	explicit OffersList(double offset, double step = 0.1);
	int operator[](double price) const;
	int& operator[](double price);
	iterator begin();
//	const_iterator begin() const{
//		return const_iterator(offers.data(), offers.data(), offset, step);
//	}

	const std::vector<int>& get_offers() const;
	double get_offset() const;
	double get_step() const;
private:
	std::vector<int>	offers;
	double			offset;
	double			step;
};

std::ostream& operator<<(std::ostream& os, const OffersList& order_book);