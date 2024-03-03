#pragma once

namespace vending_machine_state
{
class VendingMachineState {
public:
    virtual void displayOptions() const = 0;
    virtual void selectTicket(int ticketIndex, double& totalAmount) = 0;
    virtual void selectNumberOfTickets(int num, double totalOrderValue) = 0;
    virtual void insertCoin(double value, double& totalAmount) = 0;
    virtual void buyTicket() = 0;
};

};