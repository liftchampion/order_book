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
	bg->amount = 8;

	bg++;
	bg->amount = 11;
	bg++;
	//bg->amount = 20;
	cout << order_book << endl << endl;

	return 0;
}