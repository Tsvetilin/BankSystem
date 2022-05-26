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

	virtual bool withdraw(double amount) override {
		if (amount < 0) {
			return false;
		}

		if (balance - amount < 0) {
			return false;
		}

		balance -= amount;
		return true;
	}

	virtual void display(std::ostream& stream) const override {
		stream << "Account type: normal" << std::endl;
		Account::display(stream);
	}

	virtual bool serialize(std::ostream& stream) const override {
		Account::serialize(stream);
	}

	virtual bool deserialize(std::istream& stream) override {
		Account::deserialize(stream);
	}
};