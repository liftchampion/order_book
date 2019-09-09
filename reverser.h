/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 13:44:02 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 13:44:02 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

template <typename T>
class ReverseIterator {
public:
	ReverseIterator(T& container) : container(container)
	{}
	typename T::const_reverse_iterator begin() const {
		return container.crbegin();
	}
	typename T::const_reverse_iterator end() const {
		return container.crend();
	}
private:
	T& container;
};

template <typename T>
auto reverse(T& container) {
	return ReverseIterator<T>(container);
}
