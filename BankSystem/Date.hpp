#pragma once
#include <ctime>

class Date {
	bool bc;
	size_t year;
	size_t month;
	size_t day;

public:
	Date(time_t dateTime) {

	}

	static Date now() {
		return Date(time(0));
	}
};