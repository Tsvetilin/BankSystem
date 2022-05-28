#pragma once
#include "App.hpp"
#include "Bank.hpp"

const String DEFAULT_DATABASE_PATH = "bank.db";
const String DEFAULT_ERROR_MESSAGE = "Error, something went wrong! Invalid command!";

class BankSystem :public App<Bank> {

	Bank* bank;

	size_t getNumerInputInRange(std::ostream& outputStream, std::istream& inputStream, size_t lowerBound, size_t upperBound) {
		size_t option = 0;
		while (true) {
			outputStream << ">>";
			size_t option = parseToUInt(getline(inputStream));
			if (option >= lowerBound && option <= upperBound) {
				return option;
			}
			outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
		}
	}
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
			"2. Account" << std::endl <<
			"3. Exit" << std::endl;
	}

	void printEditOptionMenu(std::ostream& outputStream) {
		outputStream <<
			"1. Add" << std::endl <<
			"2. Delete" << std::endl <<
			"3. Exit" << std::endl;
	}

	void printListMenu(std::ostream& outputStream) {
		outputStream <<
			"1. List all customers" << std::endl <<
			"2. List all accounts" << std::endl <<
			"3. List customer account" << std::endl <<
			"4. List log" << std::endl <<
			"5. Exit" << std::endl;
	}

	void printActionMenu(std::ostream& outputStream) {
		outputStream <<
			"1. Withdraw from account" << std::endl <<
			"2. Deposit to account" << std::endl <<
			"3. Transfer" << std::endl <<
			"4. Exit" << std::endl;
	}

	void handleCustomerEdit(std::ostream& outputStream, std::istream& inputStream) {
		printEditOptionMenu(outputStream);

		size_t option = getNumerInputInRange(outputStream, inputStream, 1, 3);
		switch (option)
		{
		case 3: return;
		case 1: {
			outputStream << "Customer name: ";
			String name = std::move(getline(inputStream));
			outputStream << "Customer address: ";
			String address = std::move(getline(inputStream));

			if (!bank->addCustomer(name, address)) {
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

			if (!bank->deleteCustomer(parseToUInt(id))) {
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

	AccountType readAccountType(std::ostream& outputStream, std::istream& inputStream) {
		outputStream << "Chose account type:" << std::endl <<
			"1. Normal account" << std::endl <<
			"2. Savings account" << std::endl <<
			"3. Privilege account" << std::endl;

		size_t option = getNumerInputInRange(outputStream, inputStream, 1, 3);
		switch (option)
		{
		case 1: return AccountType::Normal;
		case 2: return AccountType::Savings;
		case 3: return AccountType::Privilege;
		default:
			outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
			break;
		}

		return AccountType::Unknown;
	}

	void handleAccountEdit(std::ostream& outputStream, std::istream& inputStream) {
		printEditOptionMenu(outputStream);


		size_t option = getNumerInputInRange(outputStream, inputStream, 1, 3);
		switch (option)
		{
		case 3: return;
		case 1: {
			outputStream << "Account username: ";
			String username = std::move(getline(inputStream));
			outputStream << "Account password: ";
			String password = std::move(getline(inputStream));

			outputStream << "Account iban: ";
			String iban = std::move(getline(inputStream));
			while (!validateIban(iban)) {
				if (iban == "-1") {
					return;
				}
				outputStream << "Invalid iban! Enter new (-1 to terminate the proccess): ";
				iban = std::move(getline(inputStream));
			}

			outputStream << "Customer id: ";
			size_t userId = parseToUInt(getline(inputStream));
			while (!bank->customerExists(userId)) {
				if (userId == 0) {
					return;
				}
				outputStream << "Invalid customer id! Enter new (-1 to terminate the proccess): ";
				userId = parseToUInt(getline(inputStream));
			}

			AccountType accountType = readAccountType(outputStream, inputStream);
			outputStream << "Amount: ";
			double amount = parseToDouble(getline(inputStream));

			bool success = false;
			if (accountType == AccountType::Savings) {
				outputStream << "Interest rate: ";
				double interestRate = parseToDouble(getline(inputStream));
				while (interestRate <= 0 || interestRate >= 1) {
					outputStream << "Invalid interest rate percent. Enter new: ";
					interestRate = parseToDouble(getline(inputStream));
				}

				success = bank->addPrivilegeAccount(userId, iban, username, password, amount, interestRate);
			}
			else if (accountType == AccountType::Privilege) {
				outputStream << "Overdraft amount: ";
				double overdraft = parseToDouble(getline(inputStream));
				while (overdraft == 0) {
					outputStream << "Invalid overdraft amount. Enter new: ";
					overdraft = parseToDouble(getline(inputStream));
				}

				success = bank->addPrivilegeAccount(userId, iban, username, password, amount, overdraft);
			}
			else if (accountType == AccountType::Normal) {
				success = bank->addNormalAccount(userId, iban, username, password, amount);
			}

			if (success) {
				outputStream << "Error creating account! Invalid arguments!";
			}
			else {
				outputStream << "Successfully created account!";
			}

			return;
		}
		case 2: {
			outputStream << "Account iban: ";

			if (!bank->deleteAccount(getline(inputStream))) {
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

	void handleEdit(std::ostream& outputStream, std::istream& inputStream) {
		printEditMenu(outputStream);

		size_t option = getNumerInputInRange(outputStream, inputStream, 1, 3);
		switch (option)
		{
		case 3: return;
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

	void handleList(std::ostream& outputStream, std::istream& inputStream) {
		printListMenu(outputStream);

		size_t option = getNumerInputInRange(outputStream, inputStream, 1, 5);

		switch (option)
		{
		case 5: return;
		case 1: {
			bank->listCustomers(outputStream);
			return;
		}
		case 2: {
			bank->listAccounts(outputStream);
			return;
		}
		case 3: {
			outputStream << "Customer id: ";
			size_t id = parseToUInt(getline(inputStream));
			if (!bank->listCustomerAccount(outputStream, id)) {
				outputStream << "Error! Customer not found!" << std::endl;
			}
			return;
		}
		case 4: {
			bank->listLogs(outputStream);
			return;
		}
		default:
			outputStream << DEFAULT_ERROR_MESSAGE << std::endl;
			break;
		}
	}

	void handleAction(std::ostream& outputStream, std::istream& inputStream) {
		printActionMenu(outputStream);

		size_t option = getNumerInputInRange(outputStream, inputStream, 1, 4);
		switch (option)
		{
		case 4:return;
		case 1: {
			outputStream << "Iban: ";
			String iban = std::move(getline(inputStream));
			outputStream << "Amount: ";
			double amount = parseToDouble(getline(inputStream));
			if (!bank->withdraw(iban, amount)) {
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
			if (!bank->deposit(iban, amount)) {
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
			if (!bank->transfer(ibanFrom, ibanTo, amount)) {
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

public:
	BankSystem() :bank(nullptr) {}

	virtual void Run(Bank& bank,
		std::ostream& outputStream,
		std::istream& inputSteam,
		const String& databasePath = DEFAULT_DATABASE_PATH) override {

		this->bank = &bank;

		if (!bank.readDatabase(databasePath)) {
			outputStream <<
				"Error loading databse." << std::endl <<
				"Initializing new bank: " << std::endl <<
				"Bank name: ";
			bank.setName(getline(inputSteam));
			outputStream << "Bank address: ";
			bank.setAddress(getline(inputSteam));
		}


		while (true) {
			printMainMenu(outputStream);
			size_t option = getNumerInputInRange(outputStream, inputSteam, 1, 6);

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

		this->bank = nullptr;
	}
}
