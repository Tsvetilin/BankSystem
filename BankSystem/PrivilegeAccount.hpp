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

	virtual bool withdraw(double amount)override {
		if (amount < 0) {
			return false;
		}

		if (balance + overdraft - amount < 0) {
			return false;
		}

		balance -= amount;
		return true;
	}

	virtual void display(std::ostream& stream) const override {
		stream << "Account type: privilage" << std::endl;
		Account::display(stream);
	}

	virtual void serialize(std::ostream& stream) const override {
		Account::serialize(stream);
		serializePrimitive(stream, overdraft);
	}

	virtual void deserialize(std::istream& stream) override {
		Account::deserialize(stream);
		deserializePrimitive(stream, overdraft);
	}
};

