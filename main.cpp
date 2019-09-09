#include <iostream>
#include "offers_list.h"

#include <map>

using namespace std;

int main()
{

	map<int, string> qq;

	auto ss = qq.begin();

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

	offers_list[121.2] = 33663;
	offers_list[131.2] = 33993;
	offers_list[100.2] = 331243;


	cout << offers_list << endl << endl;


	auto ff = offers_list.find(100.2);

	ff->amount = 8;

	if (offers_list.find(1337) != offers_list.end())
		offers_list.at(1337) = 100;


	cout << offers_list << endl << "Check reverse" << endl;

	for (auto it = offers_list.rbegin(); it != offers_list.rend(); ++it) {
		cout << it->price << endl;
	}
	cout << endl;

	auto before_end = offers_list.end();
	before_end--;
	auto before_begin = offers_list.begin();
	before_begin--;
	for (auto it = before_end; it != before_begin; --it) {
		cout << it->price << endl;
	}
	cout << endl;


	return 0;
}