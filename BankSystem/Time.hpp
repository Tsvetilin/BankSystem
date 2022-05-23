class Time {
	size_t hour;
	size_t minute;
	size_t second;
	size_t nanosec;

public:
	Time(time_t time) {

	}

	static Time now() {
		return Time(time(0));
	}
};