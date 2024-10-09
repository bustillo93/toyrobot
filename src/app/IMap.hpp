#pragma once

#include <memory>

namespace map
{

class IMap
{
public:
    static constexpr int INVALID {-1};

    class Point
    {
    public:
        explicit Point(const int x, const int y) : m_x{x}, m_y{y}
        {}

        bool operator==(const Point& other) const
        {
            return X() == other.X() && Y() == other.Y();
        }

        bool IsValid() const
        {
            return m_x > INVALID && m_y > INVALID;
        }

        int X() const
        {
            return m_x;
        }

        int Y() const
        {
            return m_y;
        }

    private:
        int m_x {INVALID};
        int m_y {INVALID};
    };

    IMap() = default;
    virtual ~IMap() = default;

    virtual bool IsWithinRange(const Point& pt) const = 0;
};

using IMapPtr = std::shared_ptr<IMap>;

} // namespace map

map::IMapPtr CreateConcreteMap(const int, const int);
