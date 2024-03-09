#pragma once
#include "Time.hpp"
#include "Date.hpp"
#include "../Contracts/IPrintable.hpp"
#include "../Contracts/ISerializable.hpp"


class DateTime : public ISerializable, public IPrintable {
	Time time;
	Date date;

public:
	DateTime(Date date, Time time) :date(date), time(time) {}
	DateTime(time_t now) :date(now), time(now) {}

	static DateTime now();

	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;
	virtual void print(std::ostream& stream) const override;

	friend std::ostream& operator<<(std::ostream& stream, const DateTime& dt);

};