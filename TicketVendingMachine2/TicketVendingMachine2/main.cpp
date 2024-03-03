#include "TicketVendingMachine.hpp"
#include "MachineApp.hpp"


int main()
{
    ticket_machine::TicketVendingMachine machine;
    machine_app::runMachine(machine);
}