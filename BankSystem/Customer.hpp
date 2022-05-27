#pragma once
#include "String.hpp"
#include "common.hpp"

class Customer : public Serializable {
	static size_t idGenerator;

private:
	size_t id;
	String name;
	String address;

public:

	static void serializeGenerator(std::ostream& stream){
		serializePrimitive(stream, idGenerator);
	}

	static void deserializeGenerator(std::istream& stream) {
		deserializePrimitive(stream, idGenerator);
	}

	Customer():Customer("",""){}
	Customer(const String& name, const String& address) :id(idGenerator++), name(name), address(address) {}

	virtual void serialize(std::ostream& stream) const override {
		serializePrimitive(stream, id);
		name.serialize(stream);
		address.serialize(stream);
	}

	virtual void deserialize(std::istream& stream) override {
		deserializePrimitive(stream, id);
		name.deserialize(stream);
		address.deserialize(stream);
	}

	size_t getId()const {
		return id;
	}

	void print(std::ostream& stream) {
		stream << "Customer #" << id << " : " << name << " - address: " << address << std::endl;
	}

	friend bool matchCustomerId(Customer* const& customer, const size_t& id);
	friend bool matchCustomerName(Customer* const& customer, const String& name);
};

bool matchCustomerId(Customer* const& customer, const size_t& id) {
	return customer->id == id;
}
bool matchCustomerName(Customer* const& customer, const String& name) {
	return customer->name == name;
}

size_t Customer::idGenerator = 1;