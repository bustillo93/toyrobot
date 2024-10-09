#include "Position.hpp"

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>

namespace
{
using Sides = std::pair<localisation::Direction, localisation::Direction>; // pair<left, right>
Sides GetSides(localisation::Direction dir)
{
    using Navigation = std::unordered_map<localisation::Direction, Sides>;
    static const Navigation navigation =
    {
        {localisation::Direction::NORTH, {localisation::Direction::WEST, localisation::Direction::EAST}},
        {localisation::Direction::EAST, {localisation::Direction::NORTH, localisation::Direction::SOUTH}},
        {localisation::Direction::SOUTH, {localisation::Direction::EAST, localisation::Direction::WEST}},
        {localisation::Direction::WEST, {localisation::Direction::SOUTH, localisation::Direction::NORTH}}
    };

    if (auto itr = navigation.find(dir); itr != navigation.end())
    {
        return itr->second;
    }

    return std::make_pair(localisation::Direction::INVALID, localisation::Direction::INVALID);
}
} // anonymous namespace

namespace localisation
{

Position::Position(const int x, const int y, const Direction direction)
    : m_x(x), m_y(y), m_direction(direction)
{
}

bool Position::operator==(const Position& other) const
{
    if (this == &other)
    {
        return true;
    }
    return (GetX() == other.GetX()) && (GetY() == other.GetY()) && (GetDirection() == other.GetDirection());
}

bool Position::IsValid() const
{
    return INVALID_POS != GetX() && INVALID_POS != GetY() && Direction::INVALID != GetDirection();
}

Position Position::MoveFoward() const
{
    auto x{GetX()};
    auto y{GetY()};
    auto dir{GetDirection()};

    switch (dir)
    {
        case Direction::NORTH:
            ++y;
            break;
        case Direction::SOUTH:
            --y;
            break;
        case Direction::EAST:
            ++x;
            break;
        case Direction::WEST:
            --x;
            break;
        case Direction::INVALID:
            x = INVALID_POS;
            y = INVALID_POS;
            break;
    }
    return Position(x, y, dir);
}

int Position::GetX() const
{
    return m_x;
}

int Position::GetY() const
{
    return m_y;
}

Direction Position::GetDirection() const
{
    return m_direction;
}

void Position::SetX(const int x)
{
    m_x = x;
}

void Position::SetY(const int y)
{
    m_y = y;
}

void Position::SetDirection(const Direction dir)
{
    m_direction = dir;
}

void Position::SetDirectionToLeft()
{
    m_direction = GetSides(m_direction).first;
}

void Position::SetDirectionToRight()
{
    m_direction = GetSides(m_direction).second;
}

void Position::Reset()
{
    m_x = INVALID_POS;
    m_y = INVALID_POS;
    m_direction = Direction::INVALID;
}

std::string Position::ToString() const
{
    std::stringstream ss;
    ss << GetX() << ", " << GetY() << ", " << GetDirection();
    return ss.str();
}

const std::string Position::ToString(const Direction& dir)
{
    switch (dir)
    {
        case Direction::NORTH:
            return "NORTH";
        case Direction::SOUTH:
            return "SOUTH";
        case Direction::EAST:
            return "EAST";
        case Direction::WEST:
            return "WEST";
        case Direction::INVALID:
            return "INVALID";
    }
    return "";
}
} // namespace localisation

std::ostream& operator<<(std::ostream& os, const localisation::Direction& dir)
{
    os << localisation::Position::ToString(dir);
    return os;
}

std::ostream& operator<<(std::ostream& os, const localisation::Position& pos)
{
    os << pos.ToString();
    return os;
}
