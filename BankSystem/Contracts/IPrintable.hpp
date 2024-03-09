#pragma once
#include <iostream>

class IPrintable {
public:
	virtual void print(std::ostream& stream)const = 0;
};