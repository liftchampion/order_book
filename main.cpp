#include <iostream>
#include "offers_list.h"

using namespace std;

int main()
{
	OffersList order_book(60, 0.1);
	cout << order_book << endl;

	order_book[61.20] = 20000;

	cout << order_book << endl;


	order_book[1231.2] = 333;
	order_book[1231.2] = 33003;
	order_book[121.2] = 33663;
	order_book[131.2] = 33993;
	order_book[1266631.2] = 33333;
	order_book[100.2] = 331243;

	cout << order_book << endl;



	return 0;
}