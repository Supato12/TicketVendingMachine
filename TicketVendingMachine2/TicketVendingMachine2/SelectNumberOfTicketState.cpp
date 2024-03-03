#include <iostream>
#include "SelectNumberOfTicketState.hpp"

namespace states
{

void SelectNumberOfTicketState::displayOptions() const
{
    std::cout << "Selecting number of tickets. To cancel this and go back press 0\n";
    std::cout << "Please select number of tickets to buy (select from 1 to 20 tickets) :";
}

void SelectNumberOfTicketState::selectTicket(int, double&)
{
    std::cout << "Ticket already selected.\n";
}

void SelectNumberOfTicketState::selectNumberOfTickets(int num, double totalOrderValue)
{
    std::cout << "Selected number of tickets: " << num << "\n";
    std::cout << "Total order value: " << totalOrderValue << "\n";
}

void  SelectNumberOfTicketState::insertCoin(double, double&)
{
    std::cout << "Ticket already selected. Please insert coins.\n";
}

void SelectNumberOfTicketState::buyTicket()
{
    std::cout << "Please insert coins first.\n";
}

}