#pragma once
#include <ctime>

const size_t daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
								  31, 31, 30, 31, 30, 31 };

class Date : public Serializable {
	size_t year;
	size_t month;
	size_t day;
	bool bc;

public:
	Date(time_t dateTime): year(1970),month(0),day(0),bc(false) {

		time_t daysTillNow = dateTime / (24 * 60 * 60);

		while (daysTillNow >= 365) {
			if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
				--daysTillNow;
			}

			daysTillNow -= 365;
			++year;
		}

		time_t extraDays = daysTillNow + 1;
		bool leapYear = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);

		while (true) {

			if (month == 1 && leapYear) {
				--extraDays;
			}

			if (extraDays - daysOfMonth[month] < 0) {
				break;
			}

			++month;
			extraDays -= daysOfMonth[month];
		}

		if (extraDays > 0) {
			++month;
			day = extraDays;
		}
		else {
			if (month == 2 && leapYear)
				day = 29;
			else {
				day = daysOfMonth[month - 1];
			}
		}
	}

	static Date now() {
		return Date(time(0));
	}

	virtual bool serialize(std::ostream& stream) const override {
		serializePrimitive(stream, year);
		serializePrimitive(stream, month);
		serializePrimitive(stream, day);
		serializePrimitive(stream, bc);
	}

	virtual bool deserialize(std::istream& stream) override {
		deserializePrimitive(stream, year);
		deserializePrimitive(stream, month);
		deserializePrimitive(stream, day);
		deserializePrimitive(stream, bc);
	}

	friend std::ostream& operator<<(std::ostream& stream, const Date& dt);
};


std::ostream& operator<<(std::ostream& stream, const Date& dt) {
	stream << (dt.bc ? "BC" : "") << dt.day << "/" << dt.month << "/" << dt.year;
}


