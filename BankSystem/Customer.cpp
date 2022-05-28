#include "Customer.hpp"

size_t Customer::idGenerator = 1;

void Customer::serializeGenerator(std::ostream& stream) {
	serializePrimitive(stream, idGenerator);
}

void Customer::deserializeGenerator(std::istream& stream) {
	deserializePrimitive(stream, idGenerator);
}

void  Customer::serialize(std::ostream& stream) const {
	serializePrimitive(stream, id);
	name.serialize(stream);
	address.serialize(stream);
}

void  Customer::deserialize(std::istream& stream) {
	deserializePrimitive(stream, id);
	name.deserialize(stream);
	address.deserialize(stream);
}

size_t  Customer::getId()const {
	return id;
}

void Customer::print(std::ostream& stream) const {
	stream << "Customer #" << id << " : " << name << " - address: " << address << std::endl;
}
