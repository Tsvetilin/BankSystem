#pragma once
#include "TransactType.hpp"
#include "DateTime.hpp"
#include "Common.hpp"

class Log :public Serializable{
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
		stream << "[ " << time << " ] [ " <<
			transactTypeToString(transactType) << " ] {" << relatedUserId << "} " <<
			description << std::endl;
	}

	virtual bool serialize(std::ostream& stream) const override {
		time.serialize(stream);
		serializePrimitive(stream, transactType);
		description.serialize(stream);
		serializePrimitive(stream, relatedUserId);
	}

	virtual bool deserialize(std::istream& stream) override {
		time.deserialize(stream);
		deserializePrimitive(stream, transactType);
		description.deserialize(stream);
		deserializePrimitive(stream, relatedUserId);
	}
};