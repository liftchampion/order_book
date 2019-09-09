#pragma once

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

class LogDuration {
public:
	explicit LogDuration(const string& msg = "", int ops_count = 0)
			: message(msg + ": ")
			, start(steady_clock::now())
			, ops_count(ops_count)
	{
	}

	~LogDuration() {
		auto finish = steady_clock::now();
		auto dur = finish - start;
		cerr << message
			 << duration_cast<milliseconds>(dur).count()
			 << " ms";
		if (ops_count) {
			cerr << " (" << duration_cast<nanoseconds>(dur).count() / ops_count << " ns per op)" << endl;
		} else {
			cerr << endl;
		}
	}
private:
	string message;
	steady_clock::time_point start;
	int ops_count;
};

#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message, ops_count) \
  LogDuration UNIQ_ID(__LINE__){message, ops_count};
