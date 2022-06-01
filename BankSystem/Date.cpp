#include "Date.hpp"
#include "Common.hpp"

bool Date::isLeapYear(size_t year) {
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

Date::Date(time_t dateTime) : year(EPOCH_START_YEAR), month(0), day(0), bc(false) {

	time_t daysTillNow = dateTime / (HOURS_IN_DAY * MINUETES_IN_HOUR * SECONDS_IN_MINUTE);

	while (daysTillNow >= DAYS_IN_YEAR) {
		if (isLeapYear(year)) {
			--daysTillNow;
		}

		daysTillNow -= DAYS_IN_YEAR;
		++year;
	}

	time_t extraDays = daysTillNow + 1;
	bool leapYear = isLeapYear(year);

	while (true) {
		if (month == 1 && leapYear) {
			--extraDays;
		}

		if (extraDays - DAYS_OF_MONTH[month] < 0) {
			break;
		}

		++month;
		extraDays -= DAYS_OF_MONTH[month];
	}

	if (extraDays > 0) {
		++month;
		day = (size_t)extraDays;
	}
	else {
		day = DAYS_OF_MONTH[month - 1];

		if (month == 2 && leapYear)
		{
			++day;
		}
	}
}

Date Date::now() {
	return Date(time(0));
}

void Date::serialize(std::ostream& stream) const {
	serializePrimitive(stream, year);
	serializePrimitive(stream, month);
	serializePrimitive(stream, day);
	serializePrimitive(stream, bc);
}

void Date::deserialize(std::istream& stream) {
	deserializePrimitive(stream, year);
	deserializePrimitive(stream, month);
	deserializePrimitive(stream, day);
	deserializePrimitive(stream, bc);
}

void Date::print(std::ostream& stream) const {
	stream << (bc ? "BC" : "") << day << "/" << month << "/" << year;

}

std::ostream& operator<<(std::ostream& stream, const Date& dt) {
	dt.print(stream);
	return stream;
}
