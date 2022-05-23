#pragma once
#include "String.hpp"
#include "Date.hpp"
#include "ctime"

class Account {
private:
	Date dateOfCreation;
	size_t userId;
	String username;
	String password;

protected:
	String iban;
	double balance;

public:
	Account() :Account("","","",0){}

	Account(String username, String password, String iban, size_t userId, double amount = 0) :
		username(username),
		password(password),
		iban(iban),
		userId(userId),
		balance(amount),
		dateOfCreation(time(0)) {
	}

	bool deposit(double amount) {
		if (amount < 0) {
			return false;
		}

		balance += amount;
		return true;
	}

	virtual bool withdraw(double amount);

	virtual void display(std::ostream& stream) const {
		stream << "IBAN: " << iban << std::endl;
		stream << "Client number: " << userId << std::endl;
		stream << "Balance: " << balance << std::endl;
	}

	double getBalance()const {
		return balance;
	}

	virtual ~Account(){}
};