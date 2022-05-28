#include "DateTime.hpp"

DateTime DateTime::now() {
	return DateTime(Date::now(), Time::now());
}

void DateTime::serialize(std::ostream& stream) const {
	time.serialize(stream);
	date.serialize(stream);
}

void DateTime::deserialize(std::istream& stream) {
	time.deserialize(stream);
	date.deserialize(stream);
}

void DateTime::print(std::ostream& stream) const {
	stream << date << " " << time;
}

std::ostream& operator<<(std::ostream& stream, const DateTime& dt) {
	dt.print(stream);
	return stream;
}