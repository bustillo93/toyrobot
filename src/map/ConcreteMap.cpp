#include "IMap.hpp"

namespace map
{

class ConcreteMap : public IMap
{
public:
    ConcreteMap(const int x, const int y)
    : m_width(x), m_height(y)
    {
    }

    ~ConcreteMap() override
    {
    }

    bool IsWithinRange(const Point& pt) const override
    {
        if (not pt.IsValid())
        {
            return false;
        }

        return pt.X() < m_width && pt.Y() < m_height;
    }

private:
    int m_width {INVALID};
    int m_height {INVALID};
};

} // namespace map

map::IMapPtr CreateConcreteMap(const int width, const int height)
{
    auto mapPtr{std::make_shared<map::ConcreteMap>(width, height)};
    return mapPtr;
}
