#include "Customer.hpp"
#include "../Accounts/Account.hpp"

bool matchCustomerId(Customer* const& customer, const size_t& id) {
	return customer->id == id;
}

bool matchCustomerName(Customer* const& customer, const String& name) {
	return customer->name == name;
}

bool matchIban(Account* const& account, const String& iban) {
	return account->iban == iban;
}

bool matchUsername(Account* const& account, const String& username) {
	return account->username == username;
}