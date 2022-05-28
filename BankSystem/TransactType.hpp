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


String transactTypeToString(const TransactType& type);