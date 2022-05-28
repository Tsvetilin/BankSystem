#pragma once
#include "String.hpp"
#include "Common.hpp"

class Customer : public ISerializable {
	static size_t idGenerator;

private:
	size_t id;
	String name;
	String address;

public:
	Customer() :Customer("", "") {}
	Customer(const String& name, const String& address) :id(idGenerator++), name(name), address(address) {}

	size_t getId()const;
	void print(std::ostream& stream) const;

	static void serializeGenerator(std::ostream& stream);
	static void deserializeGenerator(std::istream& stream);
	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;

	friend bool matchCustomerId(Customer* const& customer, const size_t& id);
	friend bool matchCustomerName(Customer* const& customer, const String& name);
};

bool matchCustomerId(Customer* const& customer, const size_t& id) {
	return customer->id == id;
}

bool matchCustomerName(Customer* const& customer, const String& name) {
	return customer->name == name;
}
