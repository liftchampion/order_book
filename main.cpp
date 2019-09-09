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

	offers_list[1000.457] = 99;

	offers_list[1.45] = 0;
	offers_list[1000.457] = 0;

	offers_list[0] = 7;
	offers_list[61.20] = 0;
	offers_list[0] = 0;
	offers_list[64.4] = 0;

	offers_list.rebuild();

	//offers_list[-1] = 0;

	offers_list[61.20] = 201;
	offers_list[64.42] = 1;
	offers_list[50] = 11;

	offers_list[1231.2] = 333;
	offers_list[1231.2] = 33003;
	offers_list[121.2] = 33663;
	offers_list[131.2] = 33993;
	offers_list[1266631.2] = 33333;
	offers_list[100.2] = 331243;


	cout << offers_list << endl;

	offers_list[1266631.2] = 0;

	offers_list.shrink_to_fit();

	cout << offers_list << endl;

	cout << offers_list.empty() << endl;
	cout << offers_list.set_offset(10) << endl;

	offers_list.clear();

	cout << offers_list.empty() << endl;
	cout << offers_list.set_offset(10) << endl;

	offers_list[10] = 100;

	cout << offers_list << endl;

	return 0;
}