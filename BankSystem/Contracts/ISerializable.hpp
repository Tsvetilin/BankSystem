#pragma once
#include <iostream>

class ISerializable {
public:
	virtual void serialize(std::ostream& stream) const = 0;
	virtual void deserialize(std::istream& stream) = 0;
};