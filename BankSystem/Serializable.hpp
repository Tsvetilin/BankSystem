#pragma once
#include <iostream>

class Serializable {
public:
	virtual bool serialize(std::ostream& stream) const = 0;
	virtual bool deserialize(std::istream& stream) = 0;
};