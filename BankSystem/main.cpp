#include <iostream>
#include "System/BankSystem.hpp"
#include "Bank/Bank.hpp"

int main()
{
    Bank bank;
    BankSystem bankSystem;
    bankSystem.Run(bank, std::cout, std::cin);

    return 0;
}
