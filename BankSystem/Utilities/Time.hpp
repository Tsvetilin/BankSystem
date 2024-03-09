#pragma once
#include "../Contracts/IPrintable.hpp"
#include "../Contracts/ISerializable.hpp"

class Time : public ISerializable, public IPrintable {
	size_t hour;
	size_t minute;
	size_t second;

public:
	Time(time_t time);

	static Time now();

	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;
	virtual void print(std::ostream& stream) const override;
	friend std::ostream& operator<<(std::ostream& stream, const Time& dt);
};
