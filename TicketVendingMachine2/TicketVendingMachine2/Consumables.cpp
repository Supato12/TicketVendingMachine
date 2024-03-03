#include "Consumables.hpp"
#include <iostream>

namespace consumables
{
CoinType& operator++(CoinType& val) {
    switch (val) {
    case CoinType::groszy10:
        val = CoinType::groszy20;
        break;
    case CoinType::groszy20:
        val = CoinType::groszy50;
        break;
    case CoinType::groszy50:
        val = CoinType::zloty1;
        break;
    case CoinType::zloty1:
        val = CoinType::zloty2;
        break;
    case CoinType::zloty2:
        val = CoinType::zloty5;
        break;
    case CoinType::zloty5:
        val = CoinType::wrongCoin;
        break;
    case CoinType::wrongCoin:
        val = CoinType::groszy10;
        break;
    }
    return val;
}

std::ostream& operator<<(std::ostream& os, const CoinType& val)
{
    switch (val) {
    case CoinType::groszy10:
        os << "10 groszy";
        break;
    case CoinType::groszy20:
        os << "20 groszy";
        break;
    case CoinType::groszy50:
        os << "50 groszy";
        break;
    case CoinType::zloty1:
        os << "1 zloty";
        break;
    case CoinType::zloty2:
        os << "2 zloty";
        break;
    case CoinType::zloty5:
        os << "5 zloty";
        break;
    case CoinType::wrongCoin:
        os << "Wrong Coin";
        break;
    }
    return os;
}
}