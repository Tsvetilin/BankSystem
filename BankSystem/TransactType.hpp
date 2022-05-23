#pragma once

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