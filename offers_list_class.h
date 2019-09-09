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

std::ostream& operator<<(std::ostream& os, const OffersList& offers_list);

class OffersList {
public:
	struct Offer {
		explicit Offer(double price);
		const double	price;
		int				amount = 0;
	};
	class iterator;
	class const_iterator;
	class reverse_iterator;
	class const_reverse_iterator;

	explicit OffersList() = default;
	int				operator[](double price) const;
	int&			operator[](double price);
	int				at(double price) const;
	int&			at(double price);
	iterator		find(double price);
	const_iterator	find(double price) const;
	void			rebuild();
	bool 			set_offset(double new_offset);
	bool 			set_step(double new_step);
	bool			empty() const;
	void			clear();
	void			shrink_to_fit();
	iterator		begin();
	iterator		end();
	const_iterator	begin() const;
	const_iterator	end() const;
	const_iterator	cbegin() const;
	const_iterator	cend() const;
	reverse_iterator		rbegin();
	reverse_iterator		rend();
	const_reverse_iterator	rbegin() const;
	const_reverse_iterator	rend() const;
	const_reverse_iterator	crbegin() const;
	const_reverse_iterator	crend() const;
private:
	struct OfferData {
	public:
		OfferData(double price, double step);
		Offer		offer;
	private:
		const double step;
		friend class OffersList;
	};
	using lst_iter = decltype(std::forward_list<OfferData>().begin());
	using c_lst_iter = decltype(std::forward_list<OfferData>().cbegin());

	std::array<bool, 3>			subscript_helper(double price) const;
	std::pair<double, double>	find_min_step_offset_and_rm_empty(lst_iter no_del_iter);
	void 						rebuild_(lst_iter no_del_if_empty);
	bool						need_rebuild(double price) const;
	bool						check_price_by_step(double price) const;
	size_t						get_idx_by_price(double price) const;
	static double				get_step_by_price(double price);
	static int					last_digit_before_decimal_point(std::string_view number_str);
	static int					last_digit_after_decimal_point(std::string_view number_str);

	std::forward_list<OfferData> offers_list;
	std::vector<lst_iter>        idx_to_offer_iter;
	double                       offset = INIT_VAL;
	double                       step = INIT_VAL;
	constexpr static double      INIT_VAL = -std::numeric_limits<double>::infinity();
	constexpr static int         PRECISION = 6;
	const double                 EPSILON = pow(0.1, PRECISION);
};
