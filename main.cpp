#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>

using namespace std;


class OffersList {
private:
	void check_price(double price, const string& where) const {
		if (price - offset <= -numeric_limits<double>::epsilon()) {
			throw domain_error(
					"Price should be greater or equal than offset (" + where + ")");
		}
		double quotient = price / step;
		if (fabs(quotient - static_cast<int>(quotient)) >=
								numeric_limits<double>::epsilon()) {
			throw domain_error(
					"Price should be multiply of step (" + where + ")");
		}
	}
public:
	explicit OffersList(double offset, double step = 0.1) :
						offset(offset),
						step(step)
		{}
	int operator[](double price) const {
		check_price(price, "in operator[]");
		int idx = static_cast<int>((price - offset) / step);
		if (offers.size() <= idx) {
			return 0;
		}
		 return offers[idx];
	}
	int& operator[](double price){
		check_price(price, "in operator[]");
		int idx = static_cast<int>((price - offset) / step);
		if (offers.size() <= idx) {
			offers.resize(idx + 1, 0);
		}
		return offers[idx];
	}

    const vector<int>& get_offers() const{
		return offers;
	}
	double get_offset() const{
		return offset;
	}
	double get_step() const{
		return step;
	}
private:
	 vector<int>	offers;
	 double			offset;
	 double			step;
};

ostream& operator<<(ostream& os, const OffersList& order_book){
	double step = order_book.get_step();
	double offset = order_book.get_offset();
	const auto& offers = order_book.get_offers();
	for (size_t i = 0; i < offers.size(); ++i) {
		cout << offset + step * i << " | " << offers[i] << endl;
	}
	return os;
}

int main()
{
	OffersList order_book(60, 0.1);

	order_book[70.9] = 100;
	order_book[61.20] = 20000;



	cout << order_book << endl;
	return 0;
}