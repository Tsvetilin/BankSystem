#pragma once
#include "Account.hpp"

class NormalAccount :public Account {
public:
	NormalAccount() :Account() {}

	NormalAccount(const String& username, 
		const String& password,
		const String& iban, 
		size_t userId,
		double amount = 0) :
		Account(username, password, iban, userId, amount) {}

	virtual bool withdraw(double amount) override;
	virtual void print(std::ostream& stream) const override;
	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;
};