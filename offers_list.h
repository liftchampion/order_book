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
#include <forward_list>
#include <limits>
#include <string_view>

class OffersList {
public:

	struct Offer {
		Offer(double price, int amount) : price(price), amount(amount) {}
		double	price = 0;
		int		amount;
	};

//	class iterator : public std::iterator<std::bidirectional_iterator_tag, const Offer<int&>>
//	{
//	public:
//		iterator(int *begin, int *end, int *ptr, double offset, double step);
//		~iterator();
//		iterator operator++();
//		iterator operator++(int junk);
//		Offer<int&> operator*();
//		Offer<int&>* operator->();
//		bool operator==(const iterator& other);
//		bool operator!=(const iterator& other);
//	private:
//		int 		*begin;
//		int 		*end;
//		int			*ptr;
//		double		offset;
//		double		step;
//		Offer<int&>	*_offer_ptr = nullptr;
//	};

	explicit OffersList() = default;
	int operator[](double price) const;
	int& operator[](double price);
//	iterator begin();
//	iterator end();
	static double	get_step_by_price(double price); // todo move to private
private:
	void			check_and_rebuild_if_needed(double price);

	static int last_digit_before_decimal_point(std::string_view number_str);
	static int first_digit_after_decimal_point(std::string_view number_str);
private:
	std::vector<int>			idx_to_offer_iter;
	std::forward_list<Offer>	offers_list;
	double           			offset = INIT_VAL;
	double           			step = INIT_VAL;
	constexpr static double		INIT_VAL = -std::numeric_limits<double>::infinity();
	constexpr static int		PRECISION = 6;
};

std::ostream& operator<<(std::ostream& os, OffersList& offers_list);
