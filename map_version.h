/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_version.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:42:48 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 14:42:48 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <iostream>
#include <iomanip>

class OffersListMap {
private:
	bool subscript_helper(double price) const;
public:
	OffersListMap() = default;
	int		operator[](double price) const;
	int&	operator[](double price);
	void rebuild();
	std::map<double, int> data;
};

std::ostream& operator<<(std::ostream& os, const OffersListMap& offers_list);
