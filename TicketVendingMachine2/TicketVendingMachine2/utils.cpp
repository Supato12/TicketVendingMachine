#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include "Consumables.hpp"

namespace utils
{
consumables::CoinType convertValueToCoinType(const double value)
{
    using namespace consumables;
    if (value == 0.1)
    {
        return CoinType::groszy10;
    }
    else if (value == 0.2)
    {
        return CoinType::groszy20;
    }
    else if (value == 0.5)
    {
        return CoinType::groszy50;
    }
    else if (value == 1.0)
    {
        return CoinType::zloty1;
    }
    else if (value == 2.0)
    {
        return CoinType::zloty2;
    }
    return CoinType::zloty5;
}

double convertCoinTypeToValue(const consumables::CoinType coinType)
{
    using namespace consumables;
    switch (coinType) {
    case CoinType::groszy10:
        return 0.1;
    case CoinType::groszy20:
        return 0.2;
    case CoinType::groszy50:
        return 0.5;
    case CoinType::zloty1:
        return 1.0;
    case CoinType::zloty2:
        return 2.0;
    default:
        return 5.0;
    }
}
}