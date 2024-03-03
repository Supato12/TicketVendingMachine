#include "MachineApp.hpp"
#include <iostream>
#include "TicketVendingMachine.hpp"
#include "Consumables.hpp"
#include "IVendingMachineState.hpp"
#include "IdleState.hpp"
#include "InsertCoinsState.hpp"
#include "SelectNumberOfTicketState.hpp"
#include "utils.hpp"


namespace ui_choices
{
const std::vector<int> ticketSelection{ 0,1,2,3,4 };
const std::vector<int> numOfTickets{ 0, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
const std::vector<double> coinValues{ 0, 0.1, 0.2, 0.5, 1.0, 2.0, 5.0 };
const std::vector<int> useMachine{ 0,1 };
}

namespace
{
template <typename T>
void checkIfCancelCurrentOperations(T choice, ticket_machine::TicketVendingMachine& machine)
{
    if (choice != 0)
    {
        return;
    }
    machine.cancelCurrentOperation();
    machine_app::runMachine(machine);
}

void ticketTypeSelection(ticket_machine::TicketVendingMachine& machine)
{
    machine.displayOptions();
    auto choice = utils::choiceGetter<int>(ui_choices::ticketSelection);
    checkIfCancelCurrentOperations(choice, machine);
    machine.selectTicket(choice);
}

void ticketNumberSelection(ticket_machine::TicketVendingMachine& machine)
{
    int numOfTickets{};
    machine.displayOptions();
    numOfTickets = utils::choiceGetter<int>(ui_choices::numOfTickets);
    checkIfCancelCurrentOperations(numOfTickets, machine);
    if (numOfTickets > machine.getTicketPaperNumber())
    {
        std::cout << "\nWe apologize for inconvinience, there is not enough ticketPaper. There remains only paper for " 
            << machine.getTicketPaperNumber() << " tickets\n\n";
        ticketNumberSelection(machine);
        return;
    }
    machine.selectNumOfTickets(numOfTickets);
}

void coinInsertion(ticket_machine::TicketVendingMachine& machine)
{
    do
    {
        machine.displayOptions();
        auto coinValue = utils::choiceGetter<double>(ui_choices::coinValues);
        checkIfCancelCurrentOperations(coinValue, machine);
        machine.insertCoin(coinValue);
    } while (not machine.isAmountPaid());
}

void performBuyingTicket(ticket_machine::TicketVendingMachine& machine)
{
    
    ticketTypeSelection(machine);

    ticketNumberSelection(machine);
   
    coinInsertion(machine);

    machine_app::finishUsingMachine(machine);
}
}

namespace machine_app
{
void runMachine(ticket_machine::TicketVendingMachine& machine)
{
    std::cout << "Press 1 to use machine, press 0 to leave: ";
    auto choice = utils::choiceGetter<int>(ui_choices::useMachine);
    switch (choice)
    {
    case 1:
        system("CLS");
        performBuyingTicket(machine);
        break;
    case 0:
        exit(EXIT_SUCCESS);
        break;
    }
    runMachine(machine);
}
void finishUsingMachine(ticket_machine::TicketVendingMachine& machine)
{
    machine.buyTicket();
    runMachine(machine);
}
}