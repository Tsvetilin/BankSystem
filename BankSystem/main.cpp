#include <iostream>
#include "BankSystem.hpp"
#include "Bank.hpp"

int main()
{
    Bank bank;
    BankSystem bankSystem;
    bankSystem.Run(bank, std::cout, std::cin);

    return 0;
}
