#pragma once
#include "Account.hpp"

enum class AccountType{
	Unknown,
	Normal,
	Savings,
	Privilege
};

AccountType TypeToAccountType(Account* type);