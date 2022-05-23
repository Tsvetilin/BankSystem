#pragma once
#include "DateTime.hpp"
#include "TransactType.hpp"

class Log {
	DateTime time;
	TransactType transactType;
	String description;
	size_t relatedUserId;

public:
	Log(TransactType transactType, String description, size_t userId) : 
		transactType(transactType), 
		description(description), 
		relatedUserId(userId),
		time(DateTime::now())
	{}

	void print(std::ostream& stream) const {
		stream << "[ " << time << " ] [ " << transactType << " ] {" << relatedUserId << "} " << description << std::endl;
	}
};