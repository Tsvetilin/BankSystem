#pragma once
#include "Customer.hpp"
#include "Account.hpp"
#include "Log.hpp"
#include "List.hpp"
#include "AccountType.hpp"
#include <fstream>

class Bank : public ISerializable, public IPrintable {
	String name;
	String address;
	List<Customer*> customers;
	List<Account*> accounts;
	List<Log> logs;

	void copyFrom(const Bank& other);
	void copyAccounts(const List<Account*>& accounts);
	void copyCustomers(const List<Customer*>& customers);
	void free();

	Account* instantiateAccount(AccountType type) const;
	Account* cloneAccount(Account* account) const;

	Account* createNormalAccount(size_t userId, const String& iban, const String& username,
		const String& password, double amount) const;

	Account* createSavingsAccount(size_t userId, const String& iban, const String& username,
		const String& password, double amount, double interestRate) const;

	Account* createPrivilegeAccount(size_t userId, const String& iban, const String& username,
		const String& password, double amount, double overdraft) const;

	void printAccountsForCustomer(std::ostream& stream, size_t customerId) const;
	void printLogs(std::ostream& stream) const;

public:
	Bank() :Bank("", "") {}
	Bank(const String& name, const String& address) :name(name), address(address) {}
	Bank(const Bank& other);
	Bank& operator=(const Bank& other);
	~Bank();

	void setName(const String& name);
	void setAddress(const String& address);

	bool addNormalAccount(size_t userId, const String& iban, const String& username,
		const String& password, double amount);
	bool addSavingsAccount(size_t userId, const String& iban, const String& username,
		const String& password, double amount, double interestRate);

	bool addPrivilegeAccount(size_t userId, const String& iban, const String& username,
		const String& password, double amount, double overdraft);

	bool deleteAccount(const String& iban);
	bool addCustomer(const String& name, const String& address);
	bool deleteCustomer(const size_t& id);
	bool exportLog(const String& filePath) const;

	bool transfer(const String& fromIban, const String& toIban, double amount);
	bool withdraw(const String& fromIban, double amount);
	bool deposit(const String& toIban, double amount);

	void listCustomers(std::ostream& stream) const;
	void listAccounts(std::ostream& stream) const;
	bool listCustomerAccount(std::ostream& stream, size_t customerId) const;
	bool listCustomerAccount(std::ostream& stream, const String& customerName) const;
	void listLogs(std::ostream& stream) const;

	virtual void print(std::ostream& stream) const override;
	virtual void serialize(std::ostream& stream) const override;
	virtual void deserialize(std::istream& stream) override;

	bool readDatabase(const String& path);
	bool saveDatabase(const String& path);

	bool customerExists(size_t customerId) const;
};