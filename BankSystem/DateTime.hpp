#pragma once
#include "Time.hpp"
#include "Date.hpp"
#include "Serializable.hpp"

class DateTime: public Serializable {
	Time time;
	Date date;

public:
	DateTime(Date date, Time time):date(date),time(time) {}
	DateTime(time_t now):date(now),time(now) {}

	static DateTime now() {
		return DateTime(Date::now(), Time::now());
	}

	virtual void serialize(std::ostream& stream) const override {
		time.serialize(stream);
		date.serialize(stream);
	}

	virtual void deserialize(std::istream& stream) override {
		time.deserialize(stream);
		date.deserialize(stream);
	}

	friend std::ostream& operator<<(std::ostream& stream, const DateTime& dt);
		
};

std::ostream& operator<<(std::ostream& stream, const DateTime& dt) {
	stream << dt.date << " " << dt.time;
	return stream;
}