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

/**
 * Класс для хранения пула предложений (соответствия цены количеству).
 * Предназначен для использования в реализации "Бирежевого стакана".
 * Принцип хранения данных:
 * 		>Класс имеет offset и step.
 * 		>Они используются для преобразования цены из числа с плавающей точкой
 * 		 в индекс вектора. Преобразование осущствеляется так:
 * 		 idx = (price - offset) / step.
 * 		>Данные хранятся в структуре Offer с полями price, amount.
 * 		 Сами структуры хранятся в листе (для быстрого удаления из любого места).
 * 		 Под полученным индексом (idx) в векторе хранится итератор на соответсвующий
 * 		 элемент листа. Такая структура хранения выбрана для удобного и быстрого
 * 		 перестраивания (rebuild) контейнера и удобного использования итераторов.
 * 		 Например в range based for loop.
 * 		>Подробнее о перестраивании и хранении данных рассказывается в описании
 * 		 методов.
 * 		>Лучше всего контейнер проявляет себя в ситуациях, когда разброс цен по
 * 		 величине и точности мал, то есть "Стакан полон"
 */
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
	/**
	 * Принимает аргументом искомую цену.
	 * Если существует ненулевое предложение с
	 * такой ценой, то возвращается его размер, в иных случаях возвращается 0.
	 * Контейнер остаётся неизменным.
	 * Если цена является Inf или NaN, то выбрасывается исключение.
	 * @param price
	 * @return amount
	 */
	int				operator[](double price) const;
	/**
	 * Принимает аргументов искомую цену.
	 * Если в контейнере существует предложение с
	 * такой ценой, то возвращается его размер.
	 * Если такого предложения нет,
	 * то оно добавляется.
	 * Если предложение с данной ценой не может быть помещено в
	 * контейнер при данных значениях offset и step, то они меняются на такие,
	 * при которых это возможно. Происходит rebuild.
	 * Если новое значение сильно отличается от имеющихся, особенно если у него
	 * выше точность, после rebuild'a значительно возрастает расход памяти, а
	 * сам rebuild может занимать значительное время.
	 * Если цена является Inf или NaN, то выбрасывается исключение.
	 * @param price
	 * @return amount
	 */
	int&			operator[](double price);
	int				at(double price) const;
	int&			at(double price);
	iterator		find(double price);
	const_iterator	find(double price) const;
	/**
	 *  Удаляет из контейнера все предложения с нулевым количеством.
	 *  Если rebuild был вызван оператором[], то вставленный им элемент
	 *  не удаляется.
	 *  Для оставшихся в контейнере предложений находятся достаточные для последующего
	 *  их хранения offset и step. Таким образом rebuild может, как повысить, так
	 *  и понизить объем контейнера.
	 */
	void			rebuild();
	/**
	 * Позволяет заранее установить offset для контейнера для ускорения последующей
	 * вставки данных. Это изменения возможно только если контейнер пуст.
	 * Метод возвращает true или false в зависимости от того, было ли изменение
	 * успешным.
	 * @param new_offset
	 * @return is_success
	 */
	bool 			set_offset(double new_offset);
	/**
	 * Позволяет заранее установить step для контейнера для ускорения последующей
	 * вставки данных. Это изменения возможно только если контейнер пуст.
	 * Метод возвращает true или false в зависимости от того, было ли изменение
	 * успешным.
	 * @param new_step
	 * @return is_success
	 */
	bool 			set_step(double new_step);
	double 			get_step() const;
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
