#include <iostream>
#include "offers_list.h"
#include "profile.h"
#include <limits>
#include <random>
#include <string>

using namespace std;

void benchmark(
				int int_part_min,
				int int_part_max,
				int decimal_part_min,
				int decimal_part_max,
				int amount_min,
				int amount_max,
				int tests_count,
				string msg
			   ) {
	auto	seed = 42;
	mt19937 gen(seed);
	uniform_int_distribution<int> dist_int_part(int_part_min,int_part_max);
	uniform_int_distribution<int> dist_decimal_part(decimal_part_min,decimal_part_max);
	uniform_int_distribution<int> dist_amount(amount_min,amount_max);


	{
		LOG_DURATION(msg)
		OffersList offers_list;
		for (int i = 0; i < tests_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		cout << offers_list << endl;
	}
}


int		main()
{
	benchmark(0,100,0,10,0,1000, 1000, "hui");
	return 0;
}