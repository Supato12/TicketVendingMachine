#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include "Consumables.hpp"

namespace utils
{
template <typename T>
T choiceGetter(const std::vector<T>& possibleChoices)
 {
    T choice;
    while (!(std::cin >> choice) or 
        std::find(possibleChoices.begin(), possibleChoices.end(), choice) == possibleChoices.end())
    {
        std::cout << "\n Wrong choice, try again:";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return choice;
}



consumables::CoinType convertValueToCoinType(const double value);

double convertCoinTypeToValue(const consumables::CoinType);
}