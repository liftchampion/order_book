#include <iostream>
#include "offers_list.h"

using namespace std;

int main()
{
//	OffersList offers_list(60, 0.1);
//	cout << offers_list << endl;

//	offers_list[61.20] = 20000;

//	cout << offers_list << endl;

//	offers_list[1231.2] = 333;
//	offers_list[1231.2] = 33003;
//	offers_list[121.2] = 33663;
//	offers_list[131.2] = 33993;
//	offers_list[1266631.2] = 33333;
//	offers_list[100.2] = 331243;

	std::forward_list<int>						offers_list;
	std::vector<decltype(offers_list.begin())>	idx_to_offer_iter;

	idx_to_offer_iter.resize(100, offers_list.end()); // todo important!

	//cout << OffersList::get_step_by_price(-10060000) << endl;

//	cout << offers_list << endl;
	return 0;
}