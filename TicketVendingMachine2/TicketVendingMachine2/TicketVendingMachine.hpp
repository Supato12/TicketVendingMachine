#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "Consumables.hpp"


namespace vending_machine_state
{
class VendingMachineState;
}


namespace ticket_machine
{

struct User
{
    std::pair<consumables::TicketType, int> userOrder{};
    std::unordered_map<consumables::CoinType, int> userInput{};
    std::unordered_map<consumables::CoinType, int> userChange{};
};

class TicketVendingMachine
{

public:
    TicketVendingMachine();
    TicketVendingMachine(const TicketVendingMachine&) = default;
    TicketVendingMachine(TicketVendingMachine&&) noexcept = default;
    TicketVendingMachine& operator=(const TicketVendingMachine&) = default;
    TicketVendingMachine& operator=(TicketVendingMachine&&) noexcept = default;
    ~TicketVendingMachine() = default;

    void cancelCurrentOperation();
    void displayOptions() const;
    void selectTicket(int ticketIndex);
    void insertCoin(double value);
    void buyTicket();
    void selectNumOfTickets(int num);

    inline bool isAmountPaid() { return totalAmount <= 0; };
    inline int getTicketPaperNumber() { return numOfTicketPaper; };


private:
    void updateUserInput(double);
    void updateMachineStorageUponPurchase();
    void returnUserMoney();
    bool calculateChange();
    void clearUser();

    std::shared_ptr<vending_machine_state::VendingMachineState> currentState;

    bool isOrderCancel{ false };
    int numOfTicketPaper{};
    
    double totalAmount{};
    std::unordered_map<consumables::CoinType, int> cashStorage{};
    std::vector<consumables::Ticket> ticketsInOffer{};
    User user;
};
}