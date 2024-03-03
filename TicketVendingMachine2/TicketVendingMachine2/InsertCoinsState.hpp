#pragma once
#include "IVendingMachineState.hpp"

namespace states
{
class InsertCoinsState : public vending_machine_state::VendingMachineState
{
public:
    void displayOptions() const override;
    void selectTicket(int, double&) override;
    void selectNumberOfTickets(int, double) override;
    void insertCoin(double, double&) override;
    void buyTicket() override;
};
};