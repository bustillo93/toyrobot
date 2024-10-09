#pragma once

#include "lib/Command.hpp"
#include "lib/Position.hpp"
#include "map/IMap.hpp"

namespace app
{
class ToyRobot
{
public:
    using Action = command::Action;
    using Position = lib::localisation::Position;

    explicit ToyRobot(const map::IMapPtr& map);
    ~ToyRobot();

    void Act(const command::Action&);
    void Reset();
    const Position GetPosition() const
    {
        return m_currentPose;
    }

private:
    void Place(const command::Action::Place& placeCmd);
    void Move();
    void Right();
    void Left();
    void Report();

    Position m_currentPose;
    map::IMapPtr m_map;
};

}
