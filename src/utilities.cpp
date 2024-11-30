#include "utilities.h"
#include <random>
#include <iostream>
#include <raylib.h>
#include <intrin.h>
#include <string>

void Utilities::drawFramerate()
{
    int framerate = GetFPS();
    char framerateText[7] = "FPS: ";
    std::string intString = std::to_string(framerate);
    strcat(framerateText, intString.c_str());
    DrawText(framerateText, 20, 20, 20, WHITE);
}

int Utilities::getRandomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

int Utilities::findLowestInt(int numbers[], int arrayLength)
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

bool Utilities::tileWithinNthPerimeter(int cols, int rows, std::pair<int, int> coords, int n)
{
    if (coords.first <= n - 1 || coords.second <= n - 1) {
        return true;
    }
    if (coords.first >= cols - n || coords.second >= rows - n) {
        return true;
    }
    else {
        return false;
    }
}

std::pair<int, int> Utilities::getNeighborCoords(std::pair<int, int> coords, Direction direction)
{
    switch(direction)
    {
        case Direction::UpLeft:
            return {coords.first - 1, coords.second - 1};
            break;
        case Direction::Up:
            return {coords.first, coords.second - 1};
            break;
        case Direction::UpRight:
            return {coords.first + 1, coords.second - 1};
            break;
        case Direction::Right:
            return {coords.first + 1, coords.second};
            break;
        case Direction::DownRight:
            return {coords.first + 1, coords.second + 1};
            break;
        case Direction::Down:
            return {coords.first, coords.second + 1};
            break;
        case Direction::DownLeft:
            return {coords.first - 1, coords.second + 1};
            break;
        case Direction::Left:
            return {coords.first - 1, coords.second};
            break;
        default:
            std::cout << "Error finding tile neighbor; returned original coordinates\n";
            return {coords.first, coords.second};
            break;
    }
}

std::pair<int, int> Utilities::getRandomOrthogonalNeighborCoords(std::pair<int, int> coords)
{
    int randomInt = getRandomInt(1, 6);
    
    if (randomInt < 3) {
        return getNeighborCoords(coords, Direction::Up);
    }
    if (randomInt < 5) {
        return getNeighborCoords(coords, Direction::Left);
    }
    if (randomInt == 5) {
        return getNeighborCoords(coords, Direction::Down);
    }
    else {
        return getNeighborCoords(coords, Direction::Right);
    }
}

int Utilities::neighborsOfType(std::map<std::pair<int, int>, Tile>& tileMap, std::pair<int, int> coords, TileState stateToCheck)
{
    std::vector<Direction> directions = {Direction::UpLeft, Direction::Up, Direction::UpRight, Direction::Right, Direction::DownRight, Direction::Down, Direction::DownLeft, Direction::Left};
    int neighbors = 0;
    for (int i = 0; i < (int)directions.size(); i++)
    {
        if (tileMap[getNeighborCoords(coords, directions[i])].state == stateToCheck) {
            neighbors++;
        }
    }
    return neighbors;
}

std::pair<int, int> Utilities::getTileOffsetPosition(std::pair<int, int> coords)
{
    int x = 0 - coords.first * tileSize;
    int y = 0 - coords.second * tileSize;
    std::pair<int, int> position = {x, y};
    return position;
}

bool Utilities::entityShouldRender(Map& map, int screenX, int screenY)
{
    if (screenX > screenWidth) {return false;}
    if (screenX < 0 - tileSize) {return false;}
    if (screenY > screenHeight) {return false;}
    if (screenY < 0 - tileSize) {return false;}
    return true;
}
