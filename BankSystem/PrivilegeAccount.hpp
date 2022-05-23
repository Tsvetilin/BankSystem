#pragma once
#include "Account.hpp"

class PrivilegeAccount :public Account {
	double overdraft;

public:
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
};

