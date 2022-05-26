#pragma once
#include "Account.hpp"

class SavingsAccount :public Account {
	double interestRate;

public:
	SavingsAccount() :Account(), interestRate(0) {}

	SavingsAccount(const String& username,
		const String& password,
		const String& iban,
		size_t userId,
		double interestRate,
		double amount = 0) :
		Account(username, password, iban, userId, amount), interestRate(interestRate) {}

	virtual bool withdraw(double)override {
		return false;
	}

	virtual void display(std::ostream& stream) const override {
		stream << "Account type: savings" << std::endl;
		Account::display(stream);
	}


	virtual bool serialize(std::ostream& stream) const override {
		Account::serialize(stream);
		serializePrimitive(stream, interestRate);
	}

	virtual bool deserialize(std::istream& stream) override {
		Account::deserialize(stream);
		deserializePrimitive(stream, interestRate);
	}
};
