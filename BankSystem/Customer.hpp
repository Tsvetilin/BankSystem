#pragma once
#include "String.hpp"

class Customer : public Serializable {
	static size_t idGenerator;

private:
	size_t id;
	String name;
	String address;

public:
	Customer(const String& name, const String& address):id(idGenerator++),name(name),address(address){}


	virtual bool serialize(std::ostream& stream) const override {
		serializePrimitive(stream, id);
		name.serialize(stream);
		address.serialize(stream);
	}

	virtual bool deserialize(std::istream& stream) override {
		deserializePrimitive(stream, id);
		name.deserialize(stream);
		address.deserialize(stream);
	}
};