#pragma once
#include "../Utilities/String.hpp"

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


const String& transactTypeToString(const TransactType& type);