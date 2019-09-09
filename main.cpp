#include <iostream>
#include "offers_list.h"
#include "profile.h"
#include <random>
#include <string>
#include "map_version.h"

using namespace std;

void benchmark_insert(
				int		int_part_min,
				int		int_part_max,
				int		decimal_part_min,
				int		decimal_part_max,
				int		amount_min,
				int		amount_max,
				int		ops_count,
				const string& msg
			   )
{
	auto	seed = 42;
	mt19937 gen(seed);
	uniform_int_distribution<int> dist_int_part(int_part_min,int_part_max);
	uniform_int_distribution<int> dist_decimal_part(decimal_part_min,decimal_part_max);
	uniform_int_distribution<int> dist_amount(amount_min,amount_max);


	{
		LOG_DURATION(to_string(ops_count) + " Inserts. " + msg + " (Vector)", ops_count)
		OffersList offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
	}
	{
		LOG_DURATION(to_string(ops_count) + " Inserts. " + msg + " (Map)", ops_count)
		OffersListMap offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
	}
}

void benchmark_print(
		int		int_part_min,
		int		int_part_max,
		int		decimal_part_min,
		int		decimal_part_max,
		int		amount_min,
		int		amount_max,
		int		ops_count,
		const string& msg
)
{
	auto	seed = 42;
	mt19937 gen(seed);
	uniform_int_distribution<int> dist_int_part(int_part_min,int_part_max);
	uniform_int_distribution<int> dist_decimal_part(decimal_part_min,decimal_part_max);
	uniform_int_distribution<int> dist_amount(amount_min,amount_max);


	{
		OffersList offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		LOG_DURATION("Print " + to_string(ops_count) + " inserts. " + msg + " (Vector)", ops_count)
		cout << offers_list << endl;
	}
	{
		OffersListMap offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		LOG_DURATION("Print " + to_string(ops_count) + " inserts. " + msg + " (Map)", ops_count)
		cout << offers_list << endl;
	}
}

void benchmark_delete(
		int		int_part_min,
		int		int_part_max,
		int		decimal_part_min,
		int		decimal_part_max,
		int		amount_min,
		int		amount_max,
		int		ops_count,
		const string& msg
)
{
	auto	seed = 42;
	mt19937 gen(seed);
	uniform_int_distribution<int> dist_int_part(int_part_min,int_part_max);
	uniform_int_distribution<int> dist_decimal_part(decimal_part_min,decimal_part_max);
	uniform_int_distribution<int> dist_amount(amount_min,amount_max);


	{
		OffersList offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		LOG_DURATION(to_string(ops_count) + " Deletions. " + msg + " (Vector)", ops_count)
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = 0;
		}
	}
	{
		OffersListMap offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		LOG_DURATION(to_string(ops_count) + " Deletions. " + msg + " (Map)", ops_count)
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = 0;
		}
	}
}

void benchmark_rebuild(
		int		int_part_min,
		int		int_part_max,
		int		decimal_part_min,
		int		decimal_part_max,
		int		amount_min,
		int		amount_max,
		int		ops_count,
		const string& msg
)
{
	auto	seed = 42;
	mt19937 gen(seed);
	uniform_int_distribution<int> dist_int_part(int_part_min,int_part_max);
	uniform_int_distribution<int> dist_decimal_part(decimal_part_min,decimal_part_max);
	uniform_int_distribution<int> dist_amount(amount_min,amount_max);


	{
		OffersList offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = 0;
		}
		LOG_DURATION(to_string(ops_count) + "inserts and deletions. Rebuild. " + msg + " (Vector)", ops_count)
		offers_list.rebuild();
	}
	{
		OffersListMap offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = 0;
		}
		LOG_DURATION(to_string(ops_count) + "inserts and deletions. Rebuild. " + msg + " (Map)", ops_count)
		offers_list.rebuild();
	}
}

void benchmark_miss_value(
		int		int_part_min,
		int		int_part_max,
		int		decimal_part_min,
		int		decimal_part_max,
		int		amount_min,
		int		amount_max,
		int		ops_count,
		const string& msg
)
{
	auto	seed = 42;
	mt19937 gen(seed);
	uniform_int_distribution<int> dist_int_part(int_part_min,int_part_max);
	uniform_int_distribution<int> dist_decimal_part(decimal_part_min,decimal_part_max);
	uniform_int_distribution<int> dist_amount(amount_min,amount_max);


	{
		OffersList offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		LOG_DURATION(to_string(ops_count) + "inserts. Miss value. " + msg + " (Vector)", ops_count)
		offers_list[int_part_min - 100] = 1337;
	}
	{
		OffersListMap offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		LOG_DURATION(to_string(ops_count) + "inserts. Miss value. " + msg + " (Map)", ops_count)
		offers_list[int_part_min - 100] = 1337;
	}
}

void benchmark_miss_step(
		int		int_part_min,
		int		int_part_max,
		int		decimal_part_min,
		int		decimal_part_max,
		int		amount_min,
		int		amount_max,
		int		ops_count,
		const string& msg
)
{
	auto	seed = 42;
	mt19937 gen(seed);
	uniform_int_distribution<int> dist_int_part(int_part_min,int_part_max);
	uniform_int_distribution<int> dist_decimal_part(decimal_part_min,decimal_part_max);
	uniform_int_distribution<int> dist_amount(amount_min,amount_max);


	{
		OffersList offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		LOG_DURATION(to_string(ops_count) + "inserts. Miss step. " + msg + " (Vector)", ops_count)
		offers_list[int_part_min + 0.1 / decimal_part_max] = 1337;
	}
	{
		OffersListMap offers_list;
		for (int i = 0; i < ops_count; ++i){
			offers_list[dist_int_part(gen) +
						static_cast<double>(dist_decimal_part(gen)) /
						decimal_part_max] = dist_amount(gen);
		}
		LOG_DURATION(to_string(ops_count) + "inserts. Miss step. " + msg + " (Map)", ops_count)
		offers_list[int_part_min + 0.1 / decimal_part_max] = 1337;
	}
}


int		main()
{
	benchmark_insert(0, 100,
					 0, 10,
					 0, 1000,
					 1'000, "Small range. Small decimal range");
	benchmark_insert(0, 100,
					 0, 10,
					 0, 1000,
					 100'000,
					 "Small range. Small decimal range");
	benchmark_insert(0, 100,
					 0, 10,
					 0, 1000,
					 1'000'000,
					 "Small range. Small decimal range");
	benchmark_insert(0, 100,
					 0, 10,
					 0, 1000,
					 10'000'000,
					 "Small range. Small decimal range");
	cerr << endl;
	benchmark_insert(0, 10000,
					 0, 10,
					 0, 1000,
					 1'000, "Big range. Small decimal range");
	benchmark_insert(0, 10000,
					 0, 10,
					 0, 1000,
					 100'000, "Big range. Small decimal range");
	benchmark_insert(0, 10000,
					 0, 10,
					 0, 1000,
					 1'000'000,
					 "Big range. Small decimal range");
	benchmark_insert(0, 10000,
					 0, 10,
					 0, 1000,
					 10'000'000,
					 "Big range. Small decimal range");
	cerr << endl;
	benchmark_insert(0, 100,
					 0, 10000,
					 0, 1000,
					 1'000, "Small range. Big decimal range");
	benchmark_insert(0, 100,
					 0, 10000,
					 0, 1000,
					 100'000, "Small range. Big decimal range");
	benchmark_insert(0, 100,
					 0, 10000,
					 0, 1000,
					 1'000'000,
					 "Small range. Big decimal range");
	benchmark_insert(0, 100,
					 0, 10000,
					 0, 1000,
					 10'000'000,
					 "Small range. Big decimal range");
	cerr << endl;
	benchmark_insert(0, 10000,
					 0, 10000,
					 0, 1000,
					 1'000, "Big range. Big decimal range");
	benchmark_insert(0, 10000,
					 0, 10000,
					 0, 1000,
					 100'000, "Big range. Big decimal range");
	benchmark_insert(0, 10000,
					 0, 10000,
					 0, 1000,
					 1'000'000,
					 "Big range. Big decimal range");
	benchmark_insert(0, 10000,
					 0, 10000,
					 0, 1000,
					 10'000'000,
					 "Big range. Big decimal range");
	cerr << endl << endl;

////////////////////////////////////////////////////////////////////////////////

	benchmark_print(0, 100,
					 0, 10,
					 0, 1000,
					 1'000, "Small range. Small decimal range");
	benchmark_print(0, 100,
					 0, 10,
					 0, 1000,
					 100'000,
					 "Small range. Small decimal range");
	benchmark_print(0, 100,
					 0, 10,
					 0, 1000,
					 1'000'000,
					 "Small range. Small decimal range");
	benchmark_print(0, 100,
					 0, 10,
					 0, 1000,
					 10'000'000,
					 "Small range. Small decimal range");
	cerr << endl;
	benchmark_print(0, 10000,
					 0, 10,
					 0, 1000,
					 1'000, "Big range. Small decimal range");
	benchmark_print(0, 10000,
					 0, 10,
					 0, 1000,
					 100'000, "Big range. Small decimal range");
	benchmark_print(0, 10000,
					 0, 10,
					 0, 1000,
					 1'000'000,
					 "Big range. Small decimal range");
	benchmark_print(0, 10000,
					 0, 10,
					 0, 1000,
					 10'000'000,
					 "Big range. Small decimal range");
	cerr << endl;
	benchmark_print(0, 100,
					 0, 10000,
					 0, 1000,
					 1'000, "Small range. Big decimal range");
	benchmark_print(0, 100,
					 0, 10000,
					 0, 1000,
					 100'000, "Small range. Big decimal range");
	benchmark_print(0, 100,
					 0, 10000,
					 0, 1000,
					 1'000'000,
					 "Small range. Big decimal range");
	benchmark_print(0, 100,
					 0, 10000,
					 0, 1000,
					 10'000'000,
					 "Small range. Big decimal range");
	cerr << endl;
	benchmark_print(0, 10000,
					 0, 10000,
					 0, 1000,
					 1'000, "Big range. Big decimal range");
	benchmark_print(0, 10000,
					 0, 10000,
					 0, 1000,
					 100'000, "Big range. Big decimal range");
	benchmark_print(0, 10000,
					 0, 10000,
					 0, 1000,
					 1'000'000,
					 "Big range. Big decimal range");
	benchmark_print(0, 10000,
					 0, 10000,
					 0, 1000,
					 10'000'000,
					 "Big range. Big decimal range");
	cerr << endl << endl;

////////////////////////////////////////////////////////////////////////////////

	benchmark_delete(0, 100,
					 0, 10,
					 0, 1000,
					 1'000, "Small range. Small decimal range");
	benchmark_delete(0, 100,
					 0, 10,
					 0, 1000,
					 100'000,
					 "Small range. Small decimal range");
	benchmark_delete(0, 100,
					 0, 10,
					 0, 1000,
					 1'000'000,
					 "Small range. Small decimal range");
	benchmark_delete(0, 100,
					 0, 10,
					 0, 1000,
					 10'000'000,
					 "Small range. Small decimal range");
	cerr << endl;
	benchmark_delete(0, 10000,
					 0, 10,
					 0, 1000,
					 1'000, "Big range. Small decimal range");
	benchmark_delete(0, 10000,
					 0, 10,
					 0, 1000,
					 100'000, "Big range. Small decimal range");
	benchmark_delete(0, 10000,
					 0, 10,
					 0, 1000,
					 1'000'000,
					 "Big range. Small decimal range");
	benchmark_delete(0, 10000,
					 0, 10,
					 0, 1000,
					 10'000'000,
					 "Big range. Small decimal range");
	cerr << endl;
	benchmark_delete(0, 100,
					 0, 10000,
					 0, 1000,
					 1'000, "Small range. Big decimal range");
	benchmark_delete(0, 100,
					 0, 10000,
					 0, 1000,
					 100'000, "Small range. Big decimal range");
	benchmark_delete(0, 100,
					 0, 10000,
					 0, 1000,
					 1'000'000,
					 "Small range. Big decimal range");
	benchmark_delete(0, 100,
					 0, 10000,
					 0, 1000,
					 10'000'000,
					 "Small range. Big decimal range");
	cerr << endl;
	benchmark_delete(0, 10000,
					 0, 10000,
					 0, 1000,
					 1'000, "Big range. Big decimal range");
	benchmark_delete(0, 10000,
					 0, 10000,
					 0, 1000,
					 100'000, "Big range. Big decimal range");
	benchmark_delete(0, 10000,
					 0, 10000,
					 0, 1000,
					 1'000'000,
					 "Big range. Big decimal range");
	benchmark_delete(0, 10000,
					 0, 10000,
					 0, 1000,
					 10'000'000,
					 "Big range. Big decimal range");
	cerr << endl << endl;

////////////////////////////////////////////////////////////////////////////////

	benchmark_rebuild(0, 100,
					  0, 10,
					  0, 1000,
					  1'000, "Small range. Small decimal range");
	benchmark_rebuild(0, 100,
					  0, 10,
					  0, 1000,
					  100'000,
					  "Small range. Small decimal range");
	benchmark_rebuild(0, 100,
					  0, 10,
					  0, 1000,
					  1'000'000,
					  "Small range. Small decimal range");
	benchmark_rebuild(0, 100,
					  0, 10,
					  0, 1000,
					  10'000'000,
					  "Small range. Small decimal range");
	cerr << endl;
	benchmark_rebuild(0, 10000,
					  0, 10,
					  0, 1000,
					  1'000, "Big range. Small decimal range");
	benchmark_rebuild(0, 10000,
					  0, 10,
					  0, 1000,
					  100'000, "Big range. Small decimal range");
	benchmark_rebuild(0, 10000,
					  0, 10,
					  0, 1000,
					  1'000'000,
					  "Big range. Small decimal range");
	benchmark_rebuild(0, 10000,
					  0, 10,
					  0, 1000,
					  10'000'000,
					  "Big range. Small decimal range");
	cerr << endl;
	benchmark_rebuild(0, 100,
					  0, 10000,
					  0, 1000,
					  1'000, "Small range. Big decimal range");
	benchmark_rebuild(0, 100,
					  0, 10000,
					  0, 1000,
					  100'000, "Small range. Big decimal range");
	benchmark_rebuild(0, 100,
					  0, 10000,
					  0, 1000,
					  1'000'000,
					  "Small range. Big decimal range");
	benchmark_rebuild(0, 100,
					  0, 10000,
					  0, 1000,
					  10'000'000,
					  "Small range. Big decimal range");
	cerr << endl;
	benchmark_rebuild(0, 10000,
					  0, 10000,
					  0, 1000,
					  1'000, "Big range. Big decimal range");
	benchmark_rebuild(0, 10000,
					  0, 10000,
					  0, 1000,
					  100'000, "Big range. Big decimal range");
	benchmark_rebuild(0, 10000,
					  0, 10000,
					  0, 1000,
					  1'000'000,
					  "Big range. Big decimal range");
	benchmark_rebuild(0, 10000,
					  0, 10000,
					  0, 1000,
					  10'000'000,
					  "Big range. Big decimal range");
	cerr << endl << endl;

////////////////////////////////////////////////////////////////////////////////

	benchmark_miss_value(0, 100,
						 0, 10,
						 0, 1000,
						 1'000, "Small range. Small decimal range");
	benchmark_miss_value(0, 100,
						 0, 10,
						 0, 1000,
						 100'000,
						 "Small range. Small decimal range");
	benchmark_miss_value(0, 100,
						 0, 10,
						 0, 1000,
						 1'000'000,
						 "Small range. Small decimal range");
	benchmark_miss_value(0, 100,
						 0, 10,
						 0, 1000,
						 10'000'000,
						 "Small range. Small decimal range");
	cerr << endl;
	benchmark_miss_value(0, 10000,
						 0, 10,
						 0, 1000,
						 1'000, "Big range. Small decimal range");
	benchmark_miss_value(0, 10000,
						 0, 10,
						 0, 1000,
						 100'000, "Big range. Small decimal range");
	benchmark_miss_value(0, 10000,
						 0, 10,
						 0, 1000,
						 1'000'000,
						 "Big range. Small decimal range");
	benchmark_miss_value(0, 10000,
						 0, 10,
						 0, 1000,
						 10'000'000,
						 "Big range. Small decimal range");
	cerr << endl;
	benchmark_miss_value(0, 100,
						 0, 10000,
						 0, 1000,
						 1'000, "Small range. Big decimal range");
	benchmark_miss_value(0, 100,
						 0, 10000,
						 0, 1000,
						 100'000, "Small range. Big decimal range");
	benchmark_miss_value(0, 100,
						 0, 10000,
						 0, 1000,
						 1'000'000,
						 "Small range. Big decimal range");
	benchmark_miss_value(0, 100,
						 0, 10000,
						 0, 1000,
						 10'000'000,
						 "Small range. Big decimal range");
	cerr << endl;
	benchmark_miss_value(0, 10000,
						 0, 10000,
						 0, 1000,
						 1'000, "Big range. Big decimal range");
	benchmark_miss_value(0, 10000,
						 0, 10000,
						 0, 1000,
						 100'000, "Big range. Big decimal range");
	benchmark_miss_value(0, 10000,
						 0, 10000,
						 0, 1000,
						 1'000'000,
						 "Big range. Big decimal range");
	benchmark_miss_value(0, 10000,
						 0, 10000,
						 0, 1000,
						 10'000'000,
						 "Big range. Big decimal range");
	cerr << endl << endl;

////////////////////////////////////////////////////////////////////////////////

	benchmark_miss_step(0, 100,
						0, 10,
						0, 1000,
						1'000, "Small range. Small decimal range");
	benchmark_miss_step(0, 100,
						0, 10,
						0, 1000,
						100'000,
						"Small range. Small decimal range");
	benchmark_miss_step(0, 100,
						0, 10,
						0, 1000,
						1'000'000,
						"Small range. Small decimal range");
	benchmark_miss_step(0, 100,
						0, 10,
						0, 1000,
						10'000'000,
						"Small range. Small decimal range");
	cerr << endl;
	benchmark_miss_step(0, 10000,
						0, 10,
						0, 1000,
						1'000, "Big range. Small decimal range");
	benchmark_miss_step(0, 10000,
						0, 10,
						0, 1000,
						100'000, "Big range. Small decimal range");
	benchmark_miss_step(0, 10000,
						0, 10,
						0, 1000,
						1'000'000,
						"Big range. Small decimal range");
	benchmark_miss_step(0, 10000,
						0, 10,
						0, 1000,
						10'000'000,
						"Big range. Small decimal range");
	cerr << endl;
	benchmark_miss_step(0, 100,
						0, 10000,
						0, 1000,
						1'000, "Small range. Big decimal range");
	benchmark_miss_step(0, 100,
						0, 10000,
						0, 1000,
						100'000, "Small range. Big decimal range");
	benchmark_miss_step(0, 100,
						0, 10000,
						0, 1000,
						1'000'000,
						"Small range. Big decimal range");
	benchmark_miss_step(0, 100,
						0, 10000,
						0, 1000,
						10'000'000,
						"Small range. Big decimal range");
	cerr << endl;
	benchmark_miss_step(0, 10000,
						0, 10000,
						0, 1000,
						1'000, "Big range. Big decimal range");
	benchmark_miss_step(0, 10000,
						0, 10000,
						0, 1000,
						100'000, "Big range. Big decimal range");
	benchmark_miss_step(0, 10000,
						0, 10000,
						0, 1000,
						1'000'000,
						"Big range. Big decimal range");
	benchmark_miss_step(0, 10000,
						0, 10000,
						0, 1000,
						10'000'000,
						"Big range. Big decimal range");
	cerr << endl << endl;
	return 0;
}