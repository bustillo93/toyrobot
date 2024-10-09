#include "CommandParser.hpp"

#include "Position.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace
{
using Position = localisation::Position;
using Direction = localisation::Direction;
static const std::unordered_map<std::string, Direction> DIRECTIONLOOKUP =
{
    {Position::ToString(Direction::NORTH), Direction::NORTH},
    {Position::ToString(Direction::SOUTH), Direction::SOUTH},
    {Position::ToString(Direction::EAST), Direction::EAST},
    {Position::ToString(Direction::WEST), Direction::WEST}
};
}

namespace cmd
{
std::optional<Action> CommandParser::Parse(const std::string& str)
{
    /// Change "," to space
    std::string inputStr{str};
    for (size_t i = 0; i < str.size(); i++)
    {
        if (inputStr[i] == ',')
        {
            inputStr[i] = ' ';
        }
    }

    /// stringstream cmd, x, y, direction
    std::string actionStr;
    int x;
    int y;
    std::string dirStr;
    std::stringstream ss(inputStr);

    auto ToUpperCase = [](std::string& str)
    {
        std::for_each(str.begin(), str.end(), [](char& c)
        {
            c = std::toupper(static_cast<unsigned char>(c));
        });
    };

    ss >> actionStr;
    ToUpperCase(actionStr);

    ss >> x;
    ss >> y;
    ss >> dirStr;

    /// convert to Action
    std::optional<Action> cmd;
    if (actionStr == "PLACE")
    {
        ToUpperCase(dirStr);
        if (auto itr = DIRECTIONLOOKUP.find(dirStr);
            itr != DIRECTIONLOOKUP.end())
        {
            cmd = {Action::Place{localisation::Position(x, y, itr->second)}};
        }
    }
    else if (actionStr == "MOVE")
    {
        cmd = {Action::Move{}};
    }
    else if (actionStr == "RIGHT")
    {
        cmd = {Action::Right{}};
    }
    else if (actionStr == "LEFT")
    {
        cmd = {Action::Left{}};
    }
    else if (actionStr == "REPORT")
    {
        cmd = {Action::Report{}};
    }

    return cmd;
}

} // namespace cmd
