#pragma once
#include "String.hpp"

enum class TransactType {
	Unknown,
	CreateAccount,
	DeleteAccount,
	CreateCustomer,
	DeleteCustomer,
	Withdraw,
	Deposit,
	Transfer,
};


String TransactTypeToString(TransactType& type) {
	switch (type)
	{
		case TransactType::CreateAccount: return "Create account";
		case TransactType::DeleteAccount: return "Delete account";
		case TransactType::DeleteCustomer: return "Delete customer";
		case TransactType::Withdraw: return "Withdraw";
		case TransactType::Deposit: return "Deposit";
		case TransactType::Transfer: return "Transfer";
		default: return "Unknown";
	}
}