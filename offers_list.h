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
#include <cmath>
#include <utility>

class OffersList {
public:

	struct Offer {
	public:
		Offer(double price, double step);
		double	price;
		int		amount = 0;
	private:
		const double step;
		friend class OffersList;
	};

///	struct OfferData {
///		double											step = 1;
///		decltype(std::forward_list<Offer>().begin())	offer_it;
///	};

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
private:
	std::forward_list<Offer>					offers_list;
	using lst_iter = decltype(offers_list.begin());
	std::vector<lst_iter>	idx_to_offer_iter;
	double           							offset = INIT_VAL;
	double           							step = INIT_VAL;
	constexpr static double						INIT_VAL = -std::numeric_limits<double>::infinity();
	constexpr static int						PRECISION = 6;
	const double								EPSILON = pow(0.1, PRECISION);
private:
	inline void					subscript_helper(double price, bool& can_fit, bool& present) const;
	void						check_and_rebuild_if_needed(double price);
	std::pair<double, double>	find_min_step_offset_and_rm_empty(lst_iter no_del_iter);
	void 						rebuild_(lst_iter no_del_if_empty);
	inline bool					need_rebuild(double price) const;
	inline bool					check_price_by_step(double price) const;
	inline size_t				get_idx_by_price(double price) const;
	static double				get_step_by_price(double price);
	static int					last_digit_before_decimal_point(std::string_view number_str);
	static int					last_digit_after_decimal_point(std::string_view number_str);
};

std::ostream& operator<<(std::ostream& os, OffersList& offers_list);
