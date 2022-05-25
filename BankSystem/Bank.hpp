#pragma once
#include "Customer.hpp"
#include "Account.hpp"
#include "Log.hpp"
#include "List.hpp"
#include "AccountType.hpp"

class Bank: public Serializable {
	String name;
	String address;
	List<Customer*> customers;
	List<Account*> accounts;
	List<Log> logs;

	void free() {
		for (size_t i = 0; i < accounts.getCount(); i++)
		{
			delete accounts[i];
		}
	}

	Account* instantiateAccount(Account* account) {
		if (PrivilegeAccount* acc = dynamic_cast<PrivilegeAccount*>(account)) {
			return new PrivilegeAccount(*acc);
		}
		else if (NormalAccount* acc = dynamic_cast<NormalAccount*>(account)) {
			return new NormalAccount(*acc);
		}
		else if (SavingsAccount* acc = dynamic_cast<SavingsAccount*>(account)) {
			return new SavingsAccount(*acc);
		}
		else {
			return nullptr;
		}
	}

	void copyAccounts(const List<Account*>& accounts) {
		for (size_t i = 0; i < accounts.getCount(); i++)
		{
			if (Account* account = instantiateAccount(accounts[i]))
			{
				this->accounts.add(account);
			}
		}
	}

	void copyCustomers(const List<Customer*>& customers) {
		for (size_t i = 0; i < customers.getCount(); i++)
		{
				this->customers.add(new Customer(*customers[i]));
		}
	}

	void copyFrom(const Bank& other) {
		name = other.name;
		address = other.address;
		copyCustomers(other.customers);
		logs = other.logs;
		copyAccounts(other.accounts);
	}

public:
	Bank() :Bank("", ""){}

	Bank(const String& name, const String& address):name(name),address(address) {}

	Bank(const Bank& other):name(other.name),address(other.address),logs(other.logs) {
		copyAccounts(other.accounts);
		copyCustomers(other.customers);
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

	bool addCustomer(const String& name, const String& address) {

	}

	bool deleteCustomer(size_t id) {

	}

	bool addAccount(size_t userId, const String& iban, AccountType type) {

	}

	bool deleteAccount(const String& iban) {

	}

	bool exportLog(String& filePath) const {

	}

	bool transfer(const String& fromIban, const String& toIban) {

	}

	void display(std::ostream& stream) const {

	}

	void listCustomers(std::ostream& stream) const {

	}

	void listAccounts(std::ostream& stream) const {

	}

	void listCustomerAccount(std::ostream& stream, size_t customerId) const {

	}

	void listCustomerAccount(std::ostream& stream, const String& customerName) const {

	}

	virtual bool serialize(std::ostream& stream) const override {

	}

	virtual bool deserialize(std::istream& stream) override {

	}
};