#include "AccountType.hpp"
#include "NormalAccount.hpp"
#include "SavingsAccount.hpp"
#include "PrivilegeAccount.hpp"

AccountType TypeToAccountType(Account* type) {
	if (dynamic_cast<PrivilegeAccount*>(type)) {
		return AccountType::Privilege;
	}
	else if (dynamic_cast<NormalAccount*>(type)) {
		return AccountType::Normal;
	}
	else if (dynamic_cast<SavingsAccount*>(type)) {
		return AccountType::Savings;
	}
	else {
		return AccountType::Unknown;
	}
}