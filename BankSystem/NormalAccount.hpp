#pragma once
#include "Account.hpp"

class NormalAccount :public Account {
public:
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