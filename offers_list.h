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
#include <array>

class OffersList;

std::ostream& operator<<(std::ostream& os, OffersList& offers_list);

class OffersList {
public:
	struct Offer;
	class iterator;

	explicit OffersList() = default;
	int			operator[](double price) const;
	int&		operator[](double price);
	int			at(double price) const;
	int&		at(double price);
	iterator	find(double price);
	// todo const_find
	void		rebuild();
	bool 		set_offset(double new_offset);
	bool 		set_step(double new_step);
	bool		empty() const;
	void		clear();
	void		shrink_to_fit();
	iterator	begin();
	iterator	end();
private:
	struct OfferData;
	using lst_iter = decltype(std::forward_list<OfferData>().begin());
public:
	struct Offer {
		explicit Offer(double price);
		const double	price;
		int				amount = 0;
	};

	class iterator : public std::iterator<std::bidirectional_iterator_tag, OfferData>
	{
	public:
		iterator(lst_iter *ptr, lst_iter *end, lst_iter lst_end);
		iterator&	operator=(const iterator& other) = delete;
		iterator	operator++();
		iterator	operator++(int junk);
		Offer		operator*() const;
		Offer*		operator->() const;
		bool		operator==(const iterator& other) const;
		bool		operator!=(const iterator& other) const;
	private:
		void		next();
	private:
		lst_iter		*ptr;
		const lst_iter	*end;
		const lst_iter	lst_end;
	};
private:
	std::array<bool, 3>			subscript_helper(double price) const;
	std::pair<double, double>	find_min_step_offset_and_rm_empty(lst_iter no_del_iter);
	void 						rebuild_(lst_iter no_del_if_empty);
	bool						need_rebuild(double price) const;
	bool						check_price_by_step(double price) const;
	size_t						get_idx_by_price(double price) const;
	static double				get_step_by_price(double price);
	static int					last_digit_before_decimal_point(std::string_view number_str);
	static int					last_digit_after_decimal_point(std::string_view number_str);
private:
	std::forward_list<OfferData> offers_list;
	std::vector<lst_iter>        idx_to_offer_iter;
	double                       offset = INIT_VAL;
	double                       step = INIT_VAL;
	constexpr static double      INIT_VAL = -std::numeric_limits<double>::infinity();
	constexpr static int         PRECISION = 6;
	const double                 EPSILON = pow(0.1, PRECISION);
private:
	struct OfferData {
	public:
		OfferData(double price, double step);
		Offer		offer;
	private:
		const double step;
		friend class OffersList;
	};
};
