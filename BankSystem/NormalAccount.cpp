#pragma once
#include "NormalAccount.hpp"

bool NormalAccount::withdraw(double amount) {
	if (amount < 0) {
		return false;
	}

	if (balance - amount < 0) {
		return false;
	}

	balance -= amount;
	return true;
}

void NormalAccount::print(std::ostream& stream) const {
	stream << "Account type: normal" << std::endl;
	Account::print(stream);
}

void NormalAccount::serialize(std::ostream& stream) const {
	Account::serialize(stream);
}

void NormalAccount::deserialize(std::istream& stream) {
	Account::deserialize(stream);
}