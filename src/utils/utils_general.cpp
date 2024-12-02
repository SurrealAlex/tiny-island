#include "utils_general.h"
#include <random>

int GeneralUtils::getRandomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

int GeneralUtils::findLowestInt(int numbers[], int arrayLength)
{
    int lowest = numbers[0];
    for (int i = 1; i < arrayLength; i++)
    {
        if (numbers[i] < lowest) {
            lowest = numbers[i];
        }
    }
    return lowest;
}

