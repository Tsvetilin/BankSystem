#pragma once
#include "String.hpp"
#include "Date.hpp"
#include "Serializable.hpp"

class Account: public Serializable {
private:
	Date dateOfCreation;
	size_t userId;
	String username;
	String password;

protected:
	String iban;
	double balance;

public:
	Account() :Account("", "", "", 0) {}

	Account(String username, String password, String iban, size_t userId, double amount = 0) :
		username(username),
		password(password),
		iban(iban),
		userId(userId),
		balance(amount),
		dateOfCreation(Date::now()) {
	}

	bool deposit(double amount) {
		if (amount < 0) {
			return false;
		}

		balance += amount;
		return true;
	}

	virtual bool withdraw(double amount) = 0;

	virtual void display(std::ostream& stream) const {
		stream << "IBAN: " << iban << std::endl;
		stream << "Client number: " << userId << std::endl;
		stream << "Balance: " << balance << std::endl;
	}

	double getBalance()const {
		return balance;
	}

	virtual bool serialize(std::ostream& stream) const override {
		dateOfCreation.serialize(stream);
		serializePrimitive(stream,userId);
		username.serialize(stream);
		password.serialize(stream);
	}

	virtual bool deserialize(std::istream& stream) override {
		dateOfCreation.deserialize(stream);
		deserializePrimitive(stream, userId);
		username.deserialize(stream);
		password.deserialize(stream);
	}

	virtual ~Account() {}
};