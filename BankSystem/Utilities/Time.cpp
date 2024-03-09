#include "Time.hpp"
#include "Common.hpp"
#include <ctime>
#include <iostream>

Time::Time(time_t time) {

	time %= (HOURS_IN_DAY * MINUETES_IN_HOUR * SECONDS_IN_MINUTE);
	hour = time / (SECONDS_IN_HOUR);
	minute = (time % (SECONDS_IN_HOUR)) / SECONDS_IN_MINUTE;
	second = (time % (SECONDS_IN_HOUR)) % SECONDS_IN_MINUTE;
}

Time Time::now() {
	return Time(time(0));
}

void Time::serialize(std::ostream& stream) const {
	serializePrimitive(stream, hour);
	serializePrimitive(stream, minute);
	serializePrimitive(stream, second);
}

void Time::deserialize(std::istream& stream) {
	deserializePrimitive(stream, hour);
	deserializePrimitive(stream, minute);
	deserializePrimitive(stream, second);
}

void Time::print(std::ostream& stream) const {
	stream << hour << ":" << minute << ":" << second;
}


std::ostream& operator<<(std::ostream& stream, const Time& dt) {
	dt.print(stream);
	return stream;
}