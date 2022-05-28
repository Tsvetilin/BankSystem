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

	virtual bool withdraw(double) override;
	virtual void print(std::ostream& stream) const override;
	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;
};
