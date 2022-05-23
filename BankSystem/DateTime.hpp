#pragma once
#include "Time.hpp"
#include "Date.hpp"

class DateTime {
	Time time;
	Date date;

public:
	DateTime(Date date, Time time):date(date),time(time) {}
	DateTime(time_t now):date(now),time(now) {}

	static DateTime now() {
		return DateTime(Date::now(), Time::now());
	}

	friend std::ostream& operator<<(std::ostream& stream, const DateTime& dt);
		
};

std::ostream& operator<<(std::ostream& stream, const DateTime& dt) {
	stream << dt.date << " " << dt.time;
}