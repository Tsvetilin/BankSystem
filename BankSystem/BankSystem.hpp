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
			"5. Quit" << std::endl;
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

	}

	void handleAction(std::ostream& outputStream, std::istream& inputStream) {

	}

public:
	virtual void Run(Bank& bank,
		std::ostream& outputStream,
		std::istream& inputSteam,
		const String& databasePath = DEFAULT_DATABASE_PATH) override {

		this->bank = bank;
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

/*
1. Edit
a. Customer
i. Add new customer
ii. Delete customer
b. Account
i. Add new account
ii. Delete account
2. List
a. List all customers
b. List all accounts
c. List customer account
d. List log
3. Action
a. Withdraw from account
b. Deposit to account
c. Transfer
4. Display info for the bank
5. Quit

*/