#pragma once
#include <iostream>

class Serializable {
public:
	virtual void serialize(std::ostream& stream) const = 0;
	virtual void deserialize(std::istream& stream) = 0;
};