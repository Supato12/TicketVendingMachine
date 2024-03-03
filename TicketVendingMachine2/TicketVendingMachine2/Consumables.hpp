#pragma once
#include <string>

namespace consumables
{

enum TicketType
{
    normal1RideOr1Hour = 1,
    normal20Min = 2,
    reduced1RideOr1Hour = 3,
    reduced20Min = 4
};

struct Ticket
{
    TicketType ticketType;
    double price;
};

enum CoinType
{
    groszy10,
    groszy20,
    groszy50,
    zloty1,
    zloty2,
    zloty5,
    wrongCoin
};

CoinType& operator++(CoinType& val);
std::ostream& operator<<(std::ostream& os, const CoinType& val);

struct Coin
{
    CoinType coinType;
    double coinValue;
};
}