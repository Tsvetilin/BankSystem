#include "TransactType.hpp"

const String CreateCustomerTransactName("Create customer");
const String CreateAccountTransactName("Create account");
const String DeleteCustomerTransactName("Delete customer");
const String DeleteAccountTransactName("Delete account");
const String WithdrawTransactName("Withdraw");
const String DepositTransactName("Deposit");
const String TransferTransactName("Transfer");
const String UnknownTransactName("Unknown");

const String& transactTypeToString(const TransactType& type) {
	switch (type)
	{
	case TransactType::CreateCustomer: return CreateCustomerTransactName;
	case TransactType::CreateAccount: return CreateAccountTransactName;
	case TransactType::DeleteAccount: return DeleteAccountTransactName;
	case TransactType::DeleteCustomer: return DeleteCustomerTransactName;
	case TransactType::Withdraw: return WithdrawTransactName;
	case TransactType::Deposit: return DepositTransactName;
	case TransactType::Transfer: return TransferTransactName;
	default: return UnknownTransactName;
	}
}