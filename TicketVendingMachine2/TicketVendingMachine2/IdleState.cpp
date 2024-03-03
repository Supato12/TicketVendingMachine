#include <iostream>
#include "IdleState.hpp"
#include "utils.hpp"

namespace states
{

void IdleState::displayOptions() const
{
    std::cout << "Welcome to the Ticket Vending Machine!\n";
    std::cout << "Select Ticket to buy, press number associated with your choice, to leave machine press '0':" << std::endl;
    std::cout << "0. Cancel\n1. Normal 1ride/60min (6zl),\n2. Normal 20min(4zl),\n3. Reduced 1ride/60min(3zl),\n4. Reduced 20min (1.80zl)\n";
    std::cout << "Choice: ";
}

void IdleState::selectTicket(int, double&)
{
    std::cout << "Ticked selected.\n";
}

void IdleState::selectNumberOfTickets(int, double)
{
    std::cout << "Please select ticket first .\n";
}

void  IdleState::insertCoin(double, double&)
{
    std::cout << "You haven't selected a ticket yet.\n";
}

void IdleState::buyTicket()
{
    std::cout << "You haven't selected a ticket yet.\n";
}

}
