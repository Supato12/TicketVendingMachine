#include <iostream>
#include "InsertCoinsState.hpp"

namespace states
{

void InsertCoinsState::displayOptions() const
{
    std::cout << "Inserting Coins \n To cancel and go back to the begining press '0' \n" 
        << "Please insert coins(0.1, 0.2, 0.5, 1.0, 2.0, 5.0) : ";
}

void InsertCoinsState::selectTicket(int, double&)
{
    std::cout << "Ticked was already selected.\n";
}

void InsertCoinsState::selectNumberOfTickets(int, double)
{
    std::cout << "Already inserting coins to buy tickets.\n";
}

void InsertCoinsState::insertCoin(double value, double& totalAmount)
{
    totalAmount -= value;
    std::cout << "Inserted coin: " << value << " PLN" << std::endl;
    totalAmount > 0 ? std::cout << "Remaining payment: " << totalAmount << " PLN\n"
        : std::cout << "Your change is " << fabs(totalAmount) << " PLN\n";
}

void InsertCoinsState::buyTicket()
{
    std::cout << "Ticket bought.\n";
}

}
