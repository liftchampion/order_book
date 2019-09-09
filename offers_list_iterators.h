/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offer_list_iterators.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:38:14 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 11:38:14 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "offers_list_class.h"



class OffersList::iterator : public std::iterator<std::bidirectional_iterator_tag, OfferData>
{
public:
	iterator(lst_iter *ptr, const lst_iter *before_begin,
			 const lst_iter *end, c_lst_iter lst_end);
	iterator&	operator=(const iterator& other) = delete;
	iterator	operator++();
	iterator	operator++(int junk);
	iterator	operator--();
	iterator	operator--(int junk);
	Offer		operator*() const;
	Offer*		operator->() const;
	bool		operator==(const iterator& other) const;
	bool		operator!=(const iterator& other) const;
private:
	void		next();
	void		prev();
private:
	lst_iter			*ptr;
	const lst_iter   	*before_begin;
	const lst_iter		*end;
	const c_lst_iter	lst_end;
};

class OffersList::const_iterator : public std::iterator<std::bidirectional_iterator_tag, OfferData>
{
public:
	const_iterator(const lst_iter *ptr, const lst_iter *before_begin,
				   const lst_iter *end, c_lst_iter lst_end);
	const_iterator&	operator=(const const_iterator& other) = delete;
	const_iterator	operator++();
	const_iterator	operator++(int junk);
	const_iterator	operator--();
	const_iterator	operator--(int junk);
	Offer			operator*() const;
	Offer*			operator->() const;
	bool			operator==(const const_iterator& other) const;
	bool			operator!=(const const_iterator& other) const;
private:
	void		next();
	void		prev();
private:
	const lst_iter		*ptr;
	const lst_iter   	*before_begin;
	const lst_iter		*end;
	const c_lst_iter	lst_end;
};

class OffersList::reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, OfferData>
{
public:
	reverse_iterator(lst_iter *ptr, const lst_iter *before_begin,
					 const lst_iter *end, c_lst_iter lst_end);
	reverse_iterator&	operator=(const reverse_iterator& other) = delete;
	reverse_iterator	operator++();
	reverse_iterator	operator++(int junk);
	reverse_iterator	operator--();
	reverse_iterator	operator--(int junk);
	Offer				operator*() const;
	Offer*				operator->() const;
	bool				operator==(const reverse_iterator& other) const;
	bool				operator!=(const reverse_iterator& other) const;
private:
	void		next();
	void		prev();
private:
	lst_iter         *ptr;
	const lst_iter   *before_begin;
	const lst_iter   *end;
	const c_lst_iter lst_end;
};

class OffersList::const_reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, OfferData>
{
public:
	const_reverse_iterator(const lst_iter *ptr, const lst_iter *before_begin,
					 	   const lst_iter *end, c_lst_iter lst_end);
	const_reverse_iterator&	operator=(const const_reverse_iterator& other) = delete;
	const_reverse_iterator	operator++();
	const_reverse_iterator	operator++(int junk);
	const_reverse_iterator	operator--();
	const_reverse_iterator	operator--(int junk);
	Offer					operator*() const;
	Offer*					operator->() const;
	bool					operator==(const const_reverse_iterator& other) const;
	bool					operator!=(const const_reverse_iterator& other) const;
private:
	void		next();
	void		prev();
private:
	const lst_iter   *ptr;
	const lst_iter   *before_begin;
	const lst_iter   *end;
	const c_lst_iter lst_end;
};
