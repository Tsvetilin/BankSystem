#pragma once
#include "TransactType.hpp"
#include "DateTime.hpp"
#include "Common.hpp"

class Log :public ISerializable,public IPrintable {
	DateTime time;
	TransactType transactType;
	String description;
	size_t relatedUserId;

public:
	Log() :Log(TransactType::Unknown, "", 0) {}

	Log(TransactType transactType, const String& description, size_t userId) :
		transactType(transactType),
		description(description),
		relatedUserId(userId),
		time(DateTime::now())
	{}

	virtual void print(std::ostream& stream) const override;
	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;

	friend std::ostream& operator<<(std::ostream& stream, const Log& log);
};

