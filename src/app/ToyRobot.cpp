#include "ToyRobot.hpp"

#include <iostream>
#include <variant>

namespace app
{
ToyRobot::ToyRobot(const map::IMapPtr& map)
    : m_map(map)
{
}

ToyRobot::~ToyRobot()
{
}

void ToyRobot::Reset()
{
    m_currentPose.Reset();
}

void ToyRobot::Act(const Action& action)
{
    if (std::holds_alternative<Action::Place>(action.cmdType))
    {
        Place(std::get<Action::Place>(action.cmdType));
    }
    else if (std::holds_alternative<Action::Move>(action.cmdType))
    {
        Move();
    }
    else if (std::holds_alternative<Action::Right>(action.cmdType))
    {
        Right();
    }
    else if (std::holds_alternative<Action::Left>(action.cmdType))
    {
        Left();
    }
    else if (std::holds_alternative<Action::Report>(action.cmdType))
    {
        Report();
    }
    else
    {
        std::cout << __PRETTY_FUNCTION__ << "Invalid action not acceptable!\n";
    }
}

void ToyRobot::Place(const Action::Place& placeCmd)
{
    /// check if newPose is within range of map
    if (m_map->IsWithinRange(Point(placeCmd.pos.GetX(), placeCmd.pos.GetY())))
    {
        m_currentPose.SetX(placeCmd.pos.GetX());
        m_currentPose.SetY(placeCmd.pos.GetY());
        m_currentPose.SetDirection(placeCmd.pos.GetDirection());
    }
}

void ToyRobot::Move()
{
    if (not m_currentPose.IsValid())
    {
        return;
    }

    auto newPose {m_currentPose.MoveFoward()};

    if (m_map->IsWithinRange(Point(newPose.GetX(), newPose.GetY())))
    {
        m_currentPose = newPose;
    }
}

void ToyRobot::Right()
{
    if (not m_currentPose.IsValid())
    {
        return;
    }
    m_currentPose.SetDirectionToRight();
}

void ToyRobot::Left()
{
    if (not m_currentPose.IsValid())
    {
        return;
    }
    m_currentPose.SetDirectionToLeft();
}

void ToyRobot::Report()
{
    if (not m_currentPose.IsValid())
    {
        return;
    }
    std::cout << "Output: " << m_currentPose << "\n";
}

}