#include "CommandParser.hpp"

#include "lib/Position.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace
{
    using Position = lib::localisation::Position;
    using Direction = lib::localisation::Direction;
    static const std::unordered_map<std::string, Direction> DIRECTIONLOOKUP =
    {
        {Position::ToString(Direction::NORTH), Direction::NORTH},
        {Position::ToString(Direction::SOUTH), Direction::SOUTH},
        {Position::ToString(Direction::EAST), Direction::EAST},
        {Position::ToString(Direction::WEST), Direction::WEST}
    };
}

namespace utils
{
std::optional<command::Action> CommandParser::Parse(const std::string& str)
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
    std::optional<command::Action> cmd;
    if (actionStr == "PLACE")
    {
        ToUpperCase(dirStr);
        if (auto itr = DIRECTIONLOOKUP.find(dirStr);
            itr != DIRECTIONLOOKUP.end())
        {
            cmd = {command::Action::Place{lib::localisation::Position(x, y, itr->second)}};
        }
    }
    else if (actionStr == "MOVE")
    {
        cmd = {command::Action::Move{}};
    }
    else if (actionStr == "RIGHT")
    {
        cmd = {command::Action::Right{}};
    }
    else if (actionStr == "LEFT")
    {
        cmd = {command::Action::Left{}};
    }
    else if (actionStr == "REPORT")
    {
        cmd = {command::Action::Report{}};
    }

    return cmd;
}

} // namespace utils
