#include <iostream>
#include "offers_list.h"

using namespace std;

int main()
{

	OffersList offers_list;
//	cout << offers_list << endl;

	offers_list[61.20] = 20000;

	offers_list[64.4] = 1;

	auto gg = offers_list.begin();
	++gg;

	gg->amount = 101;

	offers_list[1.45] = 1;

	cout << offers_list << endl;

//	cout << offers_list << endl;

//	offers_list[1231.2] = 333;
//	offers_list[1231.2] = 33003;
//	offers_list[121.2] = 33663;
//	offers_list[131.2] = 33993;
//	offers_list[1266631.2] = 33333;
//	offers_list[100.2] = 331243;

	//cout << OffersList::get_step_by_price(-10060000) << endl;

//	cout << offers_list << endl;
	return 0;
}