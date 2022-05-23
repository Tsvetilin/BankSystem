#pragma once
#include "Time.hpp"
#include "Date.hpp"

class DateTime {
	Date date;
	Time time;

public:
	DateTime(Date date, Time time):date(date),time(time) {}
	DateTime(time_t now):date(now),time(now) {}

	static DateTime now() {
		return DateTime(Date::now(), Time::now());
	}
};