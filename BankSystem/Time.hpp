#pragma once

class Time :public Serializable {
	size_t hour;
	size_t minute;
	size_t second;
	size_t nanosec;

public:
	Time(time_t time) :nanosec(0) {

		time %= (24 * 60 * 60);
		hour = time / 3600;
		minute = (time % 3600) / 60;
		second = (time % 3600) % 60;
	}

	static Time now() {
		return Time(time(0));
	}

	virtual bool serialize(std::ostream& stream) const override {
		serializePrimitive(stream, hour);
		serializePrimitive(stream, minute);
		serializePrimitive(stream, second);
		serializePrimitive(stream, nanosec);
	}

	virtual bool deserialize(std::istream& stream) override {
		deserializePrimitive(stream, hour);
		deserializePrimitive(stream, minute);
		deserializePrimitive(stream, second);
		deserializePrimitive(stream, nanosec);
	}

	friend std::ostream& operator<<(std::ostream& stream, const Time& dt);
};

std::ostream& operator<<(std::ostream& stream, const Time& dt) {
	stream << dt.hour << ":" << dt.minute << ":" << dt.second;
}