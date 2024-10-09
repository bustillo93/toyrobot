#pragma once

#include "Command.hpp"
#include "Position.hpp"
#include "IMap.hpp"

namespace app
{
class ToyRobot
{
public:
    using Action = cmd::Action;
    using Point = map::IMap::Point;
    using Position = localisation::Position;

    explicit ToyRobot(const map::IMapPtr& map);
    ~ToyRobot();

    void Act(const Action&);
    void Reset();
    const Position GetPosition() const
    {
        return m_currentPose;
    }

private:
    void Place(const Action::Place& placeCmd);
    void Move();
    void Right();
    void Left();
    void Report();

    Position m_currentPose;
    map::IMapPtr m_map;
};

}
