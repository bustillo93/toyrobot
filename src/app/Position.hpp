#pragma once

#include <optional>
#include <ostream>
#include <string>

namespace localisation
{
    enum class Direction
    {
        NORTH,
        SOUTH,
        EAST,
        WEST,
        INVALID
    };

    class Position
    {
    public:
        static constexpr int INVALID_POS {-1};

        Position(const int, const int, const Direction);
        Position() = default;
        ~Position() = default;
        bool operator==(const Position&) const;

        bool IsValid() const;
        Position MoveFoward() const;
        int GetX() const;
        int GetY() const;
        Direction GetDirection() const;
        void SetX(const int);
        void SetY(const int);
        void SetDirection(const Direction);
        void SetDirectionToLeft();
        void SetDirectionToRight();
        void Reset();

        std::string ToString() const;
        static const std::string ToString(const Direction&);

    private:
        int m_x{INVALID_POS};
        int m_y{INVALID_POS};
        Direction m_direction{Direction::INVALID};
    };

} // namespace localisation

std::ostream& operator<<(std::ostream&, const localisation::Direction&);
std::ostream& operator<<(std::ostream&, const localisation::Position&);
