#pragma once
#include "Account.hpp"

class PrivilegeAccount :public Account {
	double overdraft;

public:
	PrivilegeAccount() :Account(),overdraft(0) {}

	PrivilegeAccount(const String& username,
		const String& password,
		const String& iban,
		size_t userId,
		double overdraft,
		double amount = 0) :
		Account(username, password, iban, userId, amount),overdraft(overdraft) {}

	virtual bool withdraw(double amount)override;
	virtual void print(std::ostream& stream) const override;
	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;
};

