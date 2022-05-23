#pragma once
#include "Account.hpp"

class SavingsAccount :public Account {
	double interestRate;

public:
	virtual bool withdraw(double)override {
		return false;
	}

	virtual void display(std::ostream& stream) const override {
		stream << "Account type: savings" << std::endl;
		Account::display(stream);
	}

};
