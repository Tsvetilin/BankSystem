#pragma once
#include "Customer.hpp"
#include "Account.hpp"
#include "Log.hpp"
#include "List.hpp"
#include "AccountType.hpp"
#include <fstream>

class Bank : public Serializable {
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

		for (size_t i = 0; i < customers.getCount(); i++)
		{
			delete customers[i];
		}
	}

	Account* cloneAccount(Account* account) {
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

	Account* instantiateAccount(size_t userId, const String& iban, const String& username,
		const String& password, AccountType type, double amount, double param = 0) {
		if (type == AccountType::Normal) {
			return new NormalAccount(username, password, iban, userId, amount);
		}
		else if (type == AccountType::Savings) {
			return new SavingsAccount(username, password, iban, userId, param, amount);
		}
		else if (type == AccountType::Privilege) {
			return new PrivilegeAccount(username, password, iban, userId, param, amount);
		}
		else {
			return nullptr;
		}
	}

	Account* instantiateAccount(AccountType type) {
		if (type == AccountType::Normal) {
			return new NormalAccount();
		}
		else if (type == AccountType::Savings) {
			return new SavingsAccount();
		}
		else if (type == AccountType::Privilege) {
			return new PrivilegeAccount();
		}
		else {
			return nullptr;
		}
	}

	void copyAccounts(const List<Account*>& accounts) {
		for (size_t i = 0; i < accounts.getCount(); i++)
		{
			if (Account* account = cloneAccount(accounts[i]))
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
	Bank() :Bank("", "") {}

	Bank(const String& name, const String& address) :name(name), address(address) {}

	Bank(const Bank& other) :name(other.name), address(other.address), logs(other.logs) {
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
		customers.add(new Customer(name, address));
		return true;
	}

	bool deleteCustomer(const size_t& id) {
		int index = customers.getIndexByPredicate(matchCustomerId, id);
		if (index == -1) {
			return false;
		}

		customers.removeAt(index);
		return true;
	}

	bool addAccount(size_t userId, const String& iban, const String& username,
		const String& password, AccountType type, double amount, double param = 0) {

		int index = customers.getIndexByPredicate(matchCustomerId, userId);
		if (index == -1) {
			return false;
		}

		if (!validateIban(iban)) {
			return false;
		}

		accounts.add(instantiateAccount(userId, iban, username, password, type, amount, param));
		return true;
	}

	bool deleteAccount(const String& iban) {
		int index = accounts.getIndexByPredicate(matchIban, iban);
		if (index == -1) {
			return false;
		}

		accounts.removeAt(index);
		return true;
	}

	bool exportLog(const String& filePath) const {
		std::ofstream file(filePath.c_str());

		if (!file.is_open()) {
			return false;
		}

		for (size_t i = 0; i < logs.getCount(); i++)
		{
			file << logs[i] << std::endl;
		}

		file.close();

		return file.good();
	}

	bool transfer(const String& fromIban, const String& toIban, double amount) {
		int indexFrom = accounts.getIndexByPredicate(matchIban, fromIban);
		if (indexFrom == -1) {
			return false;
		}

		int indexTo = accounts.getIndexByPredicate(matchIban, toIban);
		if (indexTo == -1) {
			return false;
		}

		return accounts[indexFrom]->withdraw(amount) && accounts[indexTo]->deposit(amount);
	}

	void display(std::ostream& stream) const {
		stream << "Bank: " << name << std::endl;
		stream << "Address: " << address << std::endl;
		stream << "Total customers: " << customers.getCount() << std::endl;
		stream << "Total accounts: " << accounts.getCount() << std::endl;
	}

	void listCustomers(std::ostream& stream) const {
		for (size_t i = 0; i < customers.getCount(); i++)
		{
			customers[i]->print(stream);
		}
	}

	void listAccounts(std::ostream& stream) const {
		for (size_t i = 0; i < accounts.getCount(); i++)
		{
			accounts[i]->display(stream);
		}
	}

	void listCustomerAccount(std::ostream& stream, size_t customerId) const {
		for (size_t i = 0; i < accounts.getCount(); i++)
		{
			if (accounts[i]->getCustomerId() == customerId) {
				accounts[i]->display(stream);
			}
		}
	}

	void listCustomerAccount(std::ostream& stream, const String& customerName) const {
		int index = customers.getIndexByPredicate(matchCustomerName,customerName);
		if (index == -1) {
			return;
		}

		listCustomerAccount(stream, customers[index]->getId());
	}

	virtual bool serialize(std::ostream& stream) const override {
		name.serialize(stream);
		address.serialize(stream);

		serializePrimitive(stream, customers.getCount());
		for (size_t i = 0; i < customers.getCount(); i++)
		{
			customers[i]->serialize(stream);
		}

		serializePrimitive(stream, logs.getCount());
		for (size_t i = 0; i < logs.getCount(); i++)
		{
			logs[i].serialize(stream);
		}

		serializePrimitive(stream, accounts.getCount());
		for (size_t i = 0; i < accounts.getCount(); i++)
		{
			serializePrimitive(stream, TypeToAccountType(accounts[i]));
			accounts[i]->serialize(stream);
		}
	}

	virtual bool deserialize(std::istream& stream) override {
		name.deserialize(stream);
		address.deserialize(stream);

		size_t customersCount = 0;
		deserializePrimitive(stream, customersCount);
		for (size_t i = 0; i < customersCount; i++)
		{
			Customer* customer = new Customer;
			customer->deserialize(stream);
			customers.add(customer);
		}

		size_t logsCount = 0;
		deserializePrimitive(stream, logsCount);
		for (size_t i = 0; i < logsCount; i++)
		{
			Log log;
			log.deserialize(stream);
			logs.add(std::move(log));
		}

		size_t accountsCount = 0;
		deserializePrimitive(stream, accountsCount);
		for (size_t i = 0; i < accountsCount; i++)
		{
			AccountType type;
			deserializePrimitive(stream, type);
			Account* account = instantiateAccount(type);
			account->deserialize(stream);
			accounts.add(account);
		}
	}
};