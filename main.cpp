#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include "offers_list.h"

using namespace std;

int main()
{


	OffersList order_book(60, 0.1);

	order_book[61.20] = 20000;

	auto bg = order_book.begin();

	cout << order_book << endl << endl;
	////bg->amount = 8;

	order_book[1231.2] = 333;
	order_book[1231.2] = 33003;
	order_book[121.2] = 33663;
	order_book[131.2] = 33993;
	order_book[1266631.2] = 33333;
	order_book[100.2] = 331243;

	///bg++;
	///bg->amount = 11;
	///bg++;
	//bg->amount = 20;
	//cout << order_book << endl << endl;

	for (auto [price, amount] : order_book) {
		cout << price << " <-> " << amount << endl;
	}

	return 0;
}