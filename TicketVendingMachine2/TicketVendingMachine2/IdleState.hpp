#pragma once
#include "IVendingMachineState.hpp"

namespace states
{
class IdleState : public vending_machine_state::VendingMachineState
{
public:
    void displayOptions() const override;
    void selectTicket(int ticketIndex, double& totalAmount) override;
    void selectNumberOfTickets(int num, double totalOrderValue) override;
    void insertCoin(double value, double& totalAmount) override;
    void buyTicket() override;
};
};