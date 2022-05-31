#include "Bank.hpp"
#include "NormalAccount.hpp"
#include "SavingsAccount.hpp"
#include "PrivilegeAccount.hpp"
#include "FilterFunctions.hpp"

void Bank::printAccountsForCustomer(std::ostream& stream, size_t customerId) const {
	bool printed = false;
	for (size_t i = 0; i < accounts.getCount(); i++)
	{
		if (accounts[i]->getCustomerId() == customerId) {
			accounts[i]->print(stream);
			printed = true;
		}
	}

	if (!printed) {
		stream << "The customer specified has no accounts." << std::endl;
	}
}

void Bank::printLogs(std::ostream& stream) const {
	if (logs.getCount() == 0) {
		stream << "No logs." << std::endl;
	}

	for (size_t i = 0; i < logs.getCount(); i++)
	{
		logs[i].print(stream);
	}
}

void Bank::free() {
	for (size_t i = 0; i < accounts.getCount(); i++)
	{
		delete accounts[i];
	}

	for (size_t i = 0; i < customers.getCount(); i++)
	{
		delete customers[i];
	}
}

Account* Bank::cloneAccount(Account* account) const {
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

Account* Bank::createNormalAccount(size_t userId, const String& iban, const String& username,
	const String& password, double amount)const {
	return new NormalAccount(username, password, iban, userId, amount);
}

Account* Bank::createSavingsAccount(size_t userId, const String& iban, const String& username,
	const String& password, double amount, double interestRate)const {
	return new SavingsAccount(username, password, iban, userId, interestRate, amount);
}

Account* Bank::createPrivilegeAccount(size_t userId, const String& iban, const String& username,
	const String& password, double amount, double overdraft) const {
	return new PrivilegeAccount(username, password, iban, userId, overdraft, amount);
}

Account* Bank::instantiateAccount(AccountType type) const {
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

void Bank::copyAccounts(const List<Account*>& accounts) {
	this->accounts = List<Account*>(customers.getCount());

	for (size_t i = 0; i < accounts.getCount(); i++)
	{
		if (Account* account = cloneAccount(accounts[i]))
		{
			this->accounts.add(account);
		}
	}
}

void Bank::copyCustomers(const List<Customer*>& customers) {
	this->customers = List<Customer*>(customers.getCount());

	for (size_t i = 0; i < customers.getCount(); i++)
	{
		this->customers.add(new Customer(*customers[i]));
	}
}

void Bank::copyFrom(const Bank& other) {
	name = other.name;
	address = other.address;
	copyCustomers(other.customers);
	logs = other.logs;
	copyAccounts(other.accounts);
}


Bank::Bank(const Bank& other) :name(other.name), address(other.address), logs(other.logs) {
	copyAccounts(other.accounts);
	copyCustomers(other.customers);
}

Bank& Bank::operator=(const Bank& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Bank::~Bank() {
	free();
}

void Bank::setName(const String& name) {
	this->name = name;
}

void Bank::setAddress(const String& address) {
	this->address = address;
}

bool Bank::addCustomer(const String& name, const String& address) {
	Customer* customer = new Customer(name, address);
	customers.add(customer);
	logs.add(Log(TransactType::CreateCustomer, "Created customer", customer->getId()));
	return true;
}

bool Bank::deleteCustomer(const size_t& id) {
	int index = customers.getIndexByPredicate(matchCustomerId, id);
	if (index == -1) {
		return false;
	}

	logs.add(Log(TransactType::DeleteCustomer, "Deleted customer", customers[index]->getId()));
	customers.removeAt(index);
	return true;
}

bool Bank::addNormalAccount(size_t userId, const String& iban, const String& username,
	const String& password, double amount) {
	int index = customers.getIndexByPredicate(matchCustomerId, userId);
	if (index == -1) {
		return false;
	}

	if (accounts.getIndexByPredicate(matchIban, iban) != -1 || accounts.getIndexByPredicate(matchUsername, username) != -1) {
		return false;
	}

	if (!validateIban(iban)) {
		return false;
	}

	String log = "Created normal account iban: ";
	log.concat(iban).concat(" with deposit amount: ").concat(doubleToString(amount));
	logs.add(Log(TransactType::CreateAccount, log, customers[index]->getId())); accounts.add(createNormalAccount(userId, iban, username, password, amount));
	return true;
}

bool Bank::addSavingsAccount(size_t userId, const String& iban, const String& username,
	const String& password, double amount, double interestRate) {
	int index = customers.getIndexByPredicate(matchCustomerId, userId);
	if (index == -1) {
		return false;
	}

	if (accounts.getIndexByPredicate(matchIban, iban) != -1 || accounts.getIndexByPredicate(matchUsername, username) != -1) {
		return false;
	}

	if (!validateIban(iban)) {
		return false;
	}

	String log = "Created savings account iban: ";
	log.concat(iban).concat(" with deposit amount: ").concat(doubleToString(amount));
	logs.add(Log(TransactType::CreateAccount, log, customers[index]->getId())); 
	accounts.add(createSavingsAccount(userId, iban, username, password, amount, interestRate));
	return true;
}

bool Bank::addPrivilegeAccount(size_t userId, const String& iban, const String& username,
	const String& password, double amount, double overdraft) {
	int index = customers.getIndexByPredicate(matchCustomerId, userId);
	if (index == -1) {
		return false;
	}

	if (accounts.getIndexByPredicate(matchIban, iban) != -1 || accounts.getIndexByPredicate(matchUsername,username)!=-1) {
		return false;
	}

	if (!validateIban(iban)) {
		return false;
	}

	String log = "Created privilage account iban: ";
	log.concat(iban).concat(" with deposit amount: ").concat(doubleToString(amount));
	logs.add(Log(TransactType::CreateAccount, log, customers[index]->getId()));
	accounts.add(createPrivilegeAccount(userId, iban, username, password, amount, overdraft));
	return true;
}

bool Bank::deleteAccount(const String& iban) {
	int index = accounts.getIndexByPredicate(matchIban, iban);
	if (index == -1) {
		return false;
	}

	String log = "Deleted account with iban: ";
	log.concat(iban);
	logs.add(Log(TransactType::DeleteAccount, log, customers[index]->getId()));
	accounts.removeAt(index);
	return true;
}

bool Bank::exportLog(const String& filePath) const {
	std::ofstream file(filePath.c_str());

	if (!file.is_open()) {
		return false;
	}

	printLogs(file);
	file.close();
	return file.good();
}

bool Bank::transfer(const String& fromIban, const String& toIban, double amount) {
	int indexFrom = accounts.getIndexByPredicate(matchIban, fromIban);
	if (indexFrom == -1) {
		return false;
	}

	int indexTo = accounts.getIndexByPredicate(matchIban, toIban);
	if (indexTo == -1) {
		return false;
	}

	bool success = accounts[indexFrom]->withdraw(amount) && accounts[indexTo]->deposit(amount);
	if (success) {
		String log = "Transfer from iban: ";
		log.concat(fromIban).concat(" to iban:").concat(toIban).concat(" amount: ").concat(doubleToString(amount));
		logs.add(Log(TransactType::Transfer, log, accounts[indexFrom]->getCustomerId()));
	}

	return success;
}

bool Bank::withdraw(const String& fromIban, double amount) {
	int indexFrom = accounts.getIndexByPredicate(matchIban, fromIban);
	if (indexFrom == -1) {
		return false;
	}

	bool success = accounts[indexFrom]->withdraw(amount);
	if (success) {
		String log = "Withdraw money from iban: ";
		log.concat(fromIban).concat(" amount: ").concat(doubleToString(amount));
		logs.add(Log(TransactType::Withdraw, log, accounts[indexFrom]->getCustomerId()));
	}

	return success;
}

bool Bank::deposit(const String& toIban, double amount) {
	int indexTo = accounts.getIndexByPredicate(matchIban, toIban);
	if (indexTo == -1) {
		return false;
	}

	bool success = accounts[indexTo]->deposit(amount);
	if (success) {
		String log = "Deposit money to iban: ";
		log.concat(toIban).concat(" amount: ").concat(doubleToString(amount));
		logs.add(Log(TransactType::Deposit, log, accounts[indexTo]->getCustomerId()));
	}

	return success;
}


void Bank::print(std::ostream& stream) const {
	stream << "Bank: " << name << std::endl;
	stream << "Address: " << address << std::endl;
	stream << "Total customers: " << customers.getCount() << std::endl;
	stream << "Total accounts: " << accounts.getCount() << std::endl;
}

void Bank::listCustomers(std::ostream& stream) const {
	if (customers.getCount() == 0) {
		stream << "No customers added." << std::endl;
	}

	for (size_t i = 0; i < customers.getCount(); i++)
	{
		customers[i]->print(stream);
	}
}

void Bank::listAccounts(std::ostream& stream) const {
	if (accounts.getCount() == 0) {
		stream << "No accounts created." << std::endl;
	}

	for (size_t i = 0; i < accounts.getCount(); i++)
	{
		accounts[i]->print(stream);
		stream << std::endl;
	}
}

bool Bank::listCustomerAccount(std::ostream& stream, size_t customerId) const {
	if (!customerExists(customerId)) {
		return false;
	}

	printAccountsForCustomer(stream, customerId);
	return true;
}

bool Bank::listCustomerAccount(std::ostream& stream, const String& customerName) const {
	int index = customers.getIndexByPredicate(matchCustomerName, customerName);
	if (index == -1) {
		return false;
	}

	printAccountsForCustomer(stream, customers[index]->getId());
	return true;
}

void Bank::listLogs(std::ostream& stream) const {
	printLogs(stream);
}

void Bank::serialize(std::ostream& stream) const {
	name.serialize(stream);
	address.serialize(stream);

	Customer::serializeGenerator(stream);
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

void Bank::deserialize(std::istream& stream) {
	name.deserialize(stream);
	address.deserialize(stream);

	Customer::deserializeGenerator(stream);
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

bool Bank::readDatabase(const String& path) {
	// TODO: implement checksum guard

	std::ifstream file(path.c_str());
	if (!file.is_open()) {
		return false;
	}

	try {
		deserialize(file);
	}
	catch (...) {
		file.close();
		*this = Bank();
		return false;
	}

	file.close();
	return true;
}

bool Bank::saveDatabase(const String& path) {
	std::ofstream file(path.c_str());

	if (!file.is_open()) {
		return false;
	}

	try {
		serialize(file);
	}
	catch (...) {
		file.close();
		return false;
	}

	file.close();
	return true;
}

bool Bank::customerExists(size_t customerId) const {
	return customers.getIndexByPredicate(matchCustomerId, customerId) != -1;
}