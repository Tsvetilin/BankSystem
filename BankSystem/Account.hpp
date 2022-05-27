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

	Account(const String& username, const String& password, const String& iban, size_t userId, double amount = 0) :
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

	size_t getCustomerId() const {
		return userId;
	}

	virtual void serialize(std::ostream& stream) const override {
		iban.serialize(stream);
		serializePrimitive(stream, balance);
		dateOfCreation.serialize(stream);
		serializePrimitive(stream,userId);
		username.serialize(stream);
		password.serialize(stream);
	}

	virtual void deserialize(std::istream& stream) override {
		iban.deserialize(stream);
		deserializePrimitive(stream, balance);
		dateOfCreation.deserialize(stream);
		deserializePrimitive(stream, userId);
		username.deserialize(stream);
		password.deserialize(stream);
	}

	virtual ~Account() {}

	friend bool matchIban(Account* const& account, const String& iban);
};

bool matchIban(Account* const& account, const String& iban) {
	return account->iban == iban;
}