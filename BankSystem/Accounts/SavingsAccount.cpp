#pragma once
#include "SavingsAccount.hpp"
#include "../Utilities/Common.hpp"

bool SavingsAccount::withdraw(double) {
	return false;
}

void SavingsAccount::print(std::ostream& stream) const {
	stream << "Account type: savings" << std::endl;
	Account::print(stream);
	stream << "Interest rate: " << interestRate << std::endl;

}

void SavingsAccount::serialize(std::ostream& stream) const {
	Account::serialize(stream);
	serializePrimitive(stream, interestRate);
}

void SavingsAccount::deserialize(std::istream& stream) {
	Account::deserialize(stream);
	deserializePrimitive(stream, interestRate);
}