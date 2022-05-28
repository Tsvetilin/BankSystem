#include "Account.hpp"
#include "Common.hpp"

bool Account::deposit(double amount) {
	if (amount < 0) {
		return false;
	}

	balance += amount;
	return true;
}

double Account::getBalance()const {
	return balance;
}

size_t Account::getCustomerId() const {
	return userId;
}

void Account::print(std::ostream& stream) const {
	stream << "IBAN: " << iban << std::endl;
	stream << "Client number: " << userId << std::endl;
	stream << "Balance: " << balance << std::endl;
}

void Account::serialize(std::ostream& stream) const {
	iban.serialize(stream);
	serializePrimitive(stream, balance);
	dateOfCreation.serialize(stream);
	serializePrimitive(stream, userId);
	username.serialize(stream);
	password.serialize(stream);
}

void Account::deserialize(std::istream& stream) {
	iban.deserialize(stream);
	deserializePrimitive(stream, balance);
	dateOfCreation.deserialize(stream);
	deserializePrimitive(stream, userId);
	username.deserialize(stream);
	password.deserialize(stream);
}

