#include "TicketVendingMachine.hpp"
#include "Consumables.hpp"
#include "IVendingMachineState.hpp"
#include "IdleState.hpp"
#include "InsertCoinsState.hpp"
#include "SelectNumberOfTicketState.hpp"
#include <iostream>
#include <map>
#include "utils.hpp"

namespace ticket_machine
{
TicketVendingMachine::TicketVendingMachine() : currentState(std::make_shared<states::IdleState>()), totalAmount(0.0), numOfTicketPaper{5},
    cashStorage{ {consumables::CoinType::groszy10, 10},  {consumables::CoinType::groszy20, 1}, {consumables::CoinType::groszy50, 10},
                {consumables::CoinType::zloty1, 10}, {consumables::CoinType::zloty2, 0}, {consumables::CoinType::zloty5, 0} }
{
    ticketsInOffer.push_back({ consumables::Ticket{consumables::TicketType::normal1RideOr1Hour, 6.0 }});
    ticketsInOffer.push_back({ consumables::Ticket{consumables::TicketType::normal20Min, 4.0 } });
    ticketsInOffer.push_back({ consumables::Ticket{consumables::TicketType::reduced1RideOr1Hour, 3.0 } });
    ticketsInOffer.push_back({ consumables::Ticket{consumables::TicketType::reduced20Min, 1.80 } });
}

void TicketVendingMachine::cancelCurrentOperation()
{
    std::cout << "\nReturning coins due to cancel...\n";
    isOrderCancel = true;
    returnUserMoney();
    currentState = std::make_shared<states::IdleState>();
}

void TicketVendingMachine::displayOptions() const
{
    currentState->displayOptions();
}

void TicketVendingMachine::selectTicket(int ticketIndex)
{
    currentState->selectTicket(ticketIndex, totalAmount);
    user.userOrder.first = static_cast<consumables::TicketType>(ticketIndex);
    currentState = std::make_shared<states::SelectNumberOfTicketState>();
}

void TicketVendingMachine::insertCoin(double value)
{
    currentState->insertCoin(value, totalAmount);
    updateUserInput(value);
    currentState = std::make_shared<states::InsertCoinsState>();
}

void TicketVendingMachine::buyTicket()
{
    if (not calculateChange())
    {
        std::cout << "\n We are deeply sorry, there is no enough change, cancelling order, returning coins...\n\n";
        cancelCurrentOperation();
        return;
    }

    currentState->buyTicket();
    isOrderCancel = false;
    std::cout << "\nReturning change...:\n";
    updateMachineStorageUponPurchase();
    returnUserMoney();
    currentState = std::make_shared<states::IdleState>();
}

void TicketVendingMachine::selectNumOfTickets(int num)
{
    user.userOrder.second = num;
    auto selectedTicked = std::find_if(ticketsInOffer.begin(), ticketsInOffer.end(), [this](auto&& ticket)
        {
            return ticket.ticketType == static_cast<consumables::TicketType>(user.userOrder.first);
        });

    totalAmount = num * selectedTicked->price;
    currentState->selectNumberOfTickets(num, totalAmount);
    currentState = std::make_shared<states::InsertCoinsState>();
}

void TicketVendingMachine::updateUserInput(double coinValue)
{
    user.userInput[utils::convertValueToCoinType(coinValue)]++;
}

void TicketVendingMachine::updateMachineStorageUponPurchase()
{
    for (auto i = consumables::CoinType::groszy10; i < consumables::CoinType::wrongCoin; ++i)
    {
        cashStorage[i] += user.userInput[i];
    }
    numOfTicketPaper -= user.userOrder.second;
}

void TicketVendingMachine::returnUserMoney()
{
    auto& changeOrCancel = isOrderCancel ? user.userInput : user.userChange;
    for (auto i = consumables::CoinType::groszy10; i < consumables::CoinType::wrongCoin; ++i)
    {
        std::cout << "\nNumber of coins: " << i << " is: " << changeOrCancel[i];
    }
    std::cout << std::endl;
    clearUser();
}

void TicketVendingMachine::clearUser()
{
    for (auto i = consumables::CoinType::groszy10; i < consumables::CoinType::wrongCoin; ++i)
    {
        user.userInput[i] = 0;
        user.userChange[i] = 0;
    }
    user.userOrder.second = 0;
}


bool TicketVendingMachine::calculateChange()
{
    auto changeAmount = fabs(totalAmount);
    if (changeAmount <= 0)
    {
        return true;
    }

    // this up to next comment can be extracted to simplify function but for viewing purpose its in this place
    // f.e in anynomous namespace, overloaded function: std::unordered_map<consumables::CoinType, int> calculateChange(double& changeAmount);
    std::unordered_map<consumables::CoinType, int> change;
    std::vector<std::pair<consumables::CoinType, int>> descedingOrderCoins{ cashStorage.begin(), cashStorage.end() };
    std::sort(descedingOrderCoins.begin(), descedingOrderCoins.end(), [](auto&& lval, auto&& rval)
        {return lval.first > rval.first;  });

    std::cout << std::endl;
    const double tolerance = 0.0001; // comparing floating numbers may lead to UB f.e comparison of changeAmount (0.2) coinValue(0.2)
    for (auto& item: descedingOrderCoins)
    {
        auto& [coin, numOfCoins] = item;
        const auto coinValue = utils::convertCoinTypeToValue(coin);
        
        while (changeAmount >= coinValue - tolerance and numOfCoins > 0)
        {
            change[coin]++;
            changeAmount -= coinValue;
            numOfCoins -= 1;
        }
    }
    // end of possible extraction

    if (changeAmount > 0)
    {
        std::cout << "\nSorry, looks like there are not enough coins to return your change. Cancelling order...\n";
        return false;
    }
    user.userChange = change;
    return true;
}
}