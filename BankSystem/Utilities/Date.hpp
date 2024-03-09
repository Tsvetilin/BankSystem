#pragma once
#include "../Contracts/IPrintable.hpp"
#include "../Contracts/ISerializable.hpp"
#include <ctime>
#include <iostream>

class Date : public ISerializable, public IPrintable {
	size_t year;
	size_t month;
	size_t day;
	bool bc;

	bool isLeapYear(size_t year);

public:
	Date(time_t dateTime);

	static Date now();

	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;
	virtual void print(std::ostream& stream) const override;

	friend std::ostream& operator<<(std::ostream& stream, const Date& dt);
};
