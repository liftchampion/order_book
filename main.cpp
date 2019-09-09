/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:38:39 by ggerardy          #+#    #+#             */
/*   Updated: 2019/09/09 18:38:39 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <random>
#include <vector>
#include "offers_list.h"

using namespace std;

void	run_benchamrk();

int main() {
	OffersList offers_list;

	//offers_list.set_step(0.01);
	offers_list.set_offset(60);

	double val = 60.68;
	auto	seed = 42;
	mt19937 gen(seed);
	uniform_int_distribution<int> dist_amount(0, 2000);

	for (int i = 0; i < 30; ++i) {
		offers_list[val] = dist_amount(gen);
		val += 0.01;
	}
	cout << offers_list << endl << endl;

	vector<double> prices;
	for (const auto& [price, amount] : offers_list) {
		prices.push_back(price);
	}
	uniform_int_distribution<int> dist_price_idx(0, prices.size() - 1);

	for (int i = 0; i < 30; ++i) {
		offers_list[prices[dist_price_idx(gen)]] = 0;
	}
	cout << offers_list << endl;
}