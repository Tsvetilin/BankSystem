#pragma once
#include "PrivilegeAccount.hpp"
#include "../Utilities/Common.hpp"

bool PrivilegeAccount::withdraw(double amount) {
	if (amount < 0) {
		return false;
	}

	if (balance + overdraft - amount < 0) {
		return false;
	}

	balance -= amount;
	return true;
}

void PrivilegeAccount::print(std::ostream& stream) const {
	stream << "Account type: privilage" << std::endl;
	Account::print(stream);
	stream << "Overdraft amount: " << overdraft << std::endl;
}

void PrivilegeAccount::serialize(std::ostream& stream) const {
	Account::serialize(stream);
	serializePrimitive(stream, overdraft);
}

void PrivilegeAccount::deserialize(std::istream& stream) {
	Account::deserialize(stream);
	deserializePrimitive(stream, overdraft);
}

