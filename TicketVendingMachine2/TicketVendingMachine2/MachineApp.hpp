#pragma once
#include <iostream>
#include "TicketVendingMachine.hpp"
#include "Consumables.hpp"
#include "IVendingMachineState.hpp"
#include "IdleState.hpp"
#include "InsertCoinsState.hpp"
#include "SelectNumberOfTicketState.hpp"
#include "utils.hpp"



namespace machine_app
{
void runMachine(ticket_machine::TicketVendingMachine&);
void finishUsingMachine(ticket_machine::TicketVendingMachine&);
}
