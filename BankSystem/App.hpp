#pragma once
#include "String.hpp"

template<class T>
class App {
public:
	virtual void Run(T& object,std::ostream& outputStream, std::istream& inputSteam, const String& databasePath) = 0;
};