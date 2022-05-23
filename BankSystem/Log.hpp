#pragma once
#include "DateTime.hpp"
#include "TransactType.hpp"

class Log {
	DateTime time;
	TransactType transactType;
	String description;

public:
	Log(TransactType transactType, String description) : 
		transactType(transactType), 
		description(description), 
		time(DateTime::now())
	{}
};