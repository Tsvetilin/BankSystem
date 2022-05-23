#pragma once
#include "Customer.hpp"
#include "Account.hpp"
#include "Log.hpp"
#include "List.hpp"

class Bank {
	String name;
	String address;
	List<Customer> customers;
	List<Account*> accounts;
	List<Log> logs;

	void free() {
		for (size_t i = 0; i < accounts.getCount(); i++)
		{
			delete accounts[i];
		}
	}

	void copyAccounts(const List<Account*>& accounts) {
		for (size_t i = 0; i < accounts.getCount(); i++)
		{
			this->accounts.add(new Account(*accounts[i]));
		}
	}

	void copyFrom(const Bank& other) {
		name = other.name;
		address = other.address;
		customers = other.customers;
		logs = other.logs;
		copyAccounts(other.accounts);
	}

public:
	Bank() :Bank("", ""){}

	Bank(const String& name, const String& address):name(name),address(address) {}

	Bank(const Bank& other):name(other.name),address(other.address),customers(other.customers),logs(other.logs) {
		copyAccounts(other.accounts);
	}

	Bank& operator=(const Bank& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}

		return *this;
	}

	~Bank() {
		free();
	}
};