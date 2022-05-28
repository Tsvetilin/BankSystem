#pragma once
#include "App.hpp"
#include "Bank.hpp"

const String DEFAULT_DATABASE_PATH = "bank.db";
const String DEFAULT_ERROR_MESSAGE = "Error, something went wrong! Invalid command!";

class BankSystem :public App<Bank> {

	Bank* bank;

	size_t getNumerInputInRange(std::ostream& outputStream, std::istream& inputStream, size_t lowerBound, size_t upperBound)const;
	AccountType readAccountType(std::ostream& outputStream, std::istream& inputStream)const;

	void printMainMenu(std::ostream& outputStream)const;
	void printEditMenu(std::ostream& outputStream)const;
	void printEditOptionMenu(std::ostream& outputStream)const;
	void printListMenu(std::ostream& outputStream)const;
	void printActionMenu(std::ostream& outputStream)const;

	void handleList(std::ostream& outputStream, std::istream& inputStream)const;
	void handleAction(std::ostream& outputStream, std::istream& inputStream);
	void handleEdit(std::ostream& outputStream, std::istream& inputStream);
	void handleCustomerEdit(std::ostream& outputStream, std::istream& inputStream);
	void handleAccountEdit(std::ostream& outputStream, std::istream& inputStream);


public:
	BankSystem() :bank(nullptr) {}

	virtual void Run(Bank& bank,
		std::ostream& outputStream,
		std::istream& inputSteam,
		const String& databasePath = DEFAULT_DATABASE_PATH) override;
};