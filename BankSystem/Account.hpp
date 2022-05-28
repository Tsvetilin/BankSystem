#pragma once
#include "String.hpp"
#include "Date.hpp"
#include "ISerializable.hpp"
#include "IPrintable.hpp"

class Account : public ISerializable, public IPrintable {
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

	bool deposit(double amount);
	virtual bool withdraw(double amount) = 0;
	virtual void print(std::ostream& stream) const = 0;

	double getBalance()const;
	size_t getCustomerId() const;

	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;

	virtual ~Account() {}

	friend bool matchIban(Account* const& account, const String& iban);
	friend bool matchUsername(Account* const& account, const String& username);

};
