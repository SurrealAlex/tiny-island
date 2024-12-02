#include "math_utils.h"
#include <random>

int MathUtils::getRandomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

int MathUtils::findLowestInt(int numbers[], int arrayLength)
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

float MathUtils::findAngleinDegrees(int deltaX, int deltaY)
{
    float angleRadians = atan2(deltaY, deltaX);
    float angleDegrees = angleRadians * (180 / 3.1415926f);
    return angleDegrees;
}
