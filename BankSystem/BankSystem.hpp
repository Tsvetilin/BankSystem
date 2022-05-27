#pragma once
#include "App.hpp"
#include "Bank.hpp"

const String DEFAULT_DATABASE_PATH = "bank.db";
const String DEFAULT_ERROR_MESSAGE = "Error, something went wrong! Invalid command!";

class BankSystem :public App<Bank> {

	Bank& bank;

	void printMainMenu(std::ostream& outputStream) {
		outputStream <<
			"1. Edit" << std::endl <<
			"2. List" << std::endl <<
			"3. Action" << std::endl <<
			"4. Display info for the bank" << std::endl <<
			"5. Export log" << std::endl <<
			"6. Quit" << std::endl;
	}

	void printEditMenu(std::ostream& outputStream) {
		outputStream <<
			"1. Customer" << std::endl <<
			"2. Account" << std::endl;
	}

	void printEditOptionMenu(std::ostream& outputStream) {
		outputStream <<
			"1. Add" << std::endl <<
			"2. Delete" << std::endl;
	}

	void printListMenu(std::ostream& outputStream) {
		outputStream <<
			"1. List all customers" << std::endl <<
			"2. List all accounts" << std::endl <<
			"3. List customer account" << std::endl <<
			"4. List log" << std::endl;
	}

	void printActionMenu(std::ostream& outputStream) {
		outputStream <<
			"1. Withdraw from account" << std::endl <<
			"2. Deposit to account" << std::endl <<
			"3. Transfer";
	}

	void handleCustomerEdit(std::ostream& outputStream, std::istream& inputStream) {
		printEditOptionMenu(outputStream);

		while (true) {
			outputStream << ">>";
			size_t option = parseToUInt(getline(inputStream));
			switch (option)
			{
			case 1: {
				outputStream << "Customer name: ";
				String name = std::move(getline(inputStream));
				outputStream << "Customer address: ";
				String address = std::move(getline(inputStream));

				if (!bank.addCustomer(name, address)) {
					outputStream << "Error creating customer!";
				}
				else {
					outputStream << "Successfully created customer!";
				}
				return;
			}
			case 2: {
				outputStream << "Customer id: ";
				String id = std::move(getline(inputStream));

				if (!bank.deleteCustomer(parseToUInt(id))) {
					outputStream << "Error deleting customer! No id match!";
				}
				else {
					outputStream << "Successfully deleted customer!";
				}
				return;
			}
			default:
				outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
				break;
			}
		}
	}

	AccountType readAccountType(std::ostream& outputStream, std::istream& inputStream) {
		outputStream <<
			"1. Normal account" << std::endl <<
			"2. Savings account" << std::endl <<
			"3. Privilege account" << std::endl;
		while (true) {
			size_t input = parseToUInt(getline(inputStream));
			switch (input)
			{
			case 1: return AccountType::Normal;
			case 2: return AccountType::Savings;
			case 3: return AccountType::Privilege;
			default:
				outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
				break;
			}
		}

		return AccountType::Unknown;
	}

	void handleAccountEdit(std::ostream& outputStream, std::istream& inputStream) {
		printEditOptionMenu(outputStream);

		while (true) {
			outputStream << ">>";
			size_t option = parseToUInt(getline(inputStream));
			switch (option)
			{
			case 1: {
				outputStream << "Account username: ";
				String username = std::move(getline(inputStream));
				outputStream << "Account username: ";
				String password = std::move(getline(inputStream));

				outputStream << "Account iban: ";
				String iban = std::move(getline(inputStream));
				while (!validateIban(iban)) {
					outputStream << "Invalid iban! Enter new: ";
					iban = std::move(getline(inputStream));
				}

				outputStream << "Customer id: ";
				size_t userId = parseToUInt(getline(inputStream));
				while (!bank.customerExists(userId)) {
					outputStream << "Invalid customer id! Enter new: ";
					userId = parseToUInt(getline(inputStream));
				}

				AccountType accountType = readAccountType(outputStream, inputStream);
				double amount = parseToDouble(getline(inputStream));

				double param = 0;
				if (accountType == AccountType::Savings) {
					outputStream << "Interest rate: ";
					param = parseToDouble(getline(inputStream));
				}
				else if (accountType == AccountType::Privilege) {
					outputStream << "Overdraft amount: ";
					param = parseToDouble(getline(inputStream));
				}

				if (!bank.addAccount(userId, iban, username, password, accountType, amount, param)) {
					outputStream << "Error creating account! Invalid arguments!";
				}
				else {
					outputStream << "Successfully created account!";
				}
				return;
			}
			case 2: {
				outputStream << "Account iban: ";

				if (!bank.deleteAccount(getline(inputStream))) {
					outputStream << "Error deleting account! No iban match!";
				}
				else {
					outputStream << "Successfully deleted account!";
				}
				return;
			}
			default:
				outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
				break;
			}
		}
	}

	void handleEdit(std::ostream& outputStream, std::istream& inputStream) {
		printEditMenu(outputStream);
		String input;

		while (true) {
			outputStream << ">>";
			getline(inputStream, input);
			size_t option = parseToUInt(input);

			switch (option)
			{
			case 1: {
				handleCustomerEdit(outputStream, inputStream);
				return;
			}
			case 2: {
				handleAccountEdit(outputStream, inputStream);
				return;
			}
			default:
				outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
				break;
			}
		}
	}

	void handleList(std::ostream& outputStream, std::istream& inputStream) {
		printListMenu(outputStream);
		String input;

		while (true) {
			outputStream << ">>";
			input = std::move(getline(inputStream));
			size_t option = parseToUInt(input);

			switch (option)
			{
			case 1: {
				bank.listCustomers(outputStream);
				return;
			}
			case 2: {
				bank.listAccounts(outputStream);
				return;
			}
			case 3: {
				outputStream << "Customer id: ";
				size_t id = parseToUInt(getline(inputStream));
				if (!bank.listCustomerAccount(outputStream, id)) {
					outputStream << "Error! Customer not found!" << std::endl;
				}
				return;
			}
			case 4: {
				bank.listLogs(outputStream);
				return;
			}
			default:
				outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
				break;
			}
		}
	}

	void handleAction(std::ostream& outputStream, std::istream& inputStream) {
		printActionMenu(outputStream);
		String input;

		while (true) {
			outputStream << ">>";
			input = std::move(getline(inputStream));
			size_t option = parseToUInt(input);

			switch (option)
			{
			case 1: {
				outputStream << "Iban: ";
				String iban = std::move(getline(inputStream));
				outputStream << "Amount: ";
				double amount = parseToDouble(getline(inputStream));
				if (!bank.withdraw(iban, amount)) {
					outputStream << "Operation failed! Insufficient amount, denied permissions or invalid iban!" << std::endl;
				}
				else {
					outputStream << "Money successfully withdrawn!" << std::endl;
				}

				return;
			}
			case 2: {
				outputStream << "Iban: ";
				String iban = std::move(getline(inputStream));
				outputStream << "Amount: ";
				double amount = parseToDouble(getline(inputStream));
				if (!bank.deposit(iban, amount)) {
					outputStream << "Invalid iban!" << std::endl;
				}
				else {
					outputStream << "Money successfully deposited!" << std::endl;
				}

				return;
			}
			case 3: {
				outputStream << "Iban from: ";
				String ibanFrom = std::move(getline(inputStream));
				outputStream << "Iban to: ";
				String ibanTo = std::move(getline(inputStream));
				outputStream << "Amount: ";
				double amount = parseToDouble(getline(inputStream));
				if (!bank.transfer(ibanFrom, ibanTo, amount)) {
					outputStream << "Operation failed! Insufficient amount, denied permissions or invalid iban!" << std::endl;
				}
				else {
					outputStream << "Money successfully transferred!" << std::endl;
				}

				return;
			}
			default:
				outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
				break;
			}
		}
	}

public:
	BankSystem() :bank(*(Bank*)nullptr) {}

	virtual void Run(Bank& bank,
		std::ostream& outputStream,
		std::istream& inputSteam,
		const String& databasePath = DEFAULT_DATABASE_PATH) override {

		this->bank = *&bank;
		String input;

		if (!bank.readDatabase(databasePath)) {
			outputStream <<
				"Error loading databse." << std::endl <<
				"Initializing new bank: " << std::endl <<
				"Bank name: ";

			getline(inputSteam, input);
			bank.setName(input);

			outputStream << "Bank address: ";
			getline(inputSteam, input);
			bank.setAddress(input);
		}


		while (true) {
			printMainMenu(outputStream);
			outputStream << ">>";
			getline(inputSteam, input);
			size_t option = parseToUInt(input);
			switch (option)
			{
			case 1: {
				handleEdit(outputStream, inputSteam);
				break;
			}
			case 2: {
				handleList(outputStream, inputSteam);
				break;
			}
			case 3: {
				handleAction(outputStream, inputSteam);
				break;
			}
			case 4: {
				bank.display(outputStream);
				break;
			}
			case 5: {
				outputStream << "Log file path: ";
				if (!bank.exportLog(getline(inputSteam))) {
					outputStream << "Error exporting log. Proccess terminated!" << std::endl;
				}
				else {
					outputStream << "Log exported successfully." << std::endl;
				}
				break;
			}
			case 6: {
				outputStream << "Closing the bank system..." << std::endl;
				if (!bank.saveDatabase(databasePath)) {
					outputStream << "Error saving database. Proccess terminated!" << std::endl;
				}
				return;
			}
			default:
				outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
				break;
			}

			outputStream << std::endl;
		}

	}
};