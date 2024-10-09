#include "app/ToyRobot.hpp"
#include "mocks/MapMock.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;
using ::testing::Exactly;

using Action = cmd::Action;
using Direction = localisation::Direction;
using Position = localisation::Position;

struct ToyRobotShould : ::testing::Test
{
    void SetUp() override
    {
        mapMock = std::make_shared<map::mocks::MapMock>();
        sut = std::make_unique<app::ToyRobot>(mapMock);
    }

    void TearDown() override
    {
        sut.reset();
        mapMock.reset();
    }

    std::shared_ptr<map::mocks::MapMock> mapMock;
    std::unique_ptr<app::ToyRobot> sut;
};

constexpr localisation::Position INVALID_POSITION;

TEST_F(ToyRobotShould, HaveInvalidInitPosition)
{
    EXPECT_TRUE(sut->GetPosition() == INVALID_POSITION);
}

TEST_F(ToyRobotShould, IgnoreActionWithoutPlaceAndRemainWithInvalidPosition)
{
    Action notPlaceAction{{Action::Move{}}};
    sut->Act(notPlaceAction);
    EXPECT_TRUE(sut->GetPosition() == INVALID_POSITION);
}

TEST_F(ToyRobotShould, AcceptPlaceAction)
{
    constexpr int X{2};
    constexpr int Y{3};
    const Position expectedPose{X, Y, Direction::WEST};
    const map::IMap::Point pt{X, Y};
    const Action placeAction({Action::Place{expectedPose}});

    EXPECT_CALL(*mapMock, IsWithinRange(pt)).Times(Exactly(1)).WillOnce(Return(true));
    sut->Act(placeAction);

    EXPECT_TRUE(sut->GetPosition() == expectedPose);
}

TEST_F(ToyRobotShould, AcceptMoveAction)
{
    constexpr int X{2};
    constexpr int Y{3};
    const Position initialPose{X, Y, Direction::WEST};
    const Action placeAction({Action::Place{initialPose}});

    EXPECT_CALL(*mapMock, IsWithinRange(_)).WillRepeatedly(Return(true));
    sut->Act(placeAction);

    EXPECT_TRUE(sut->GetPosition() == initialPose);

    const Action moveAction{Action::Move{}};
    const Position movedPose{X-1, Y, Direction::WEST};

    sut->Act(moveAction);
    EXPECT_TRUE(sut->GetPosition() == movedPose);
}

TEST_F(ToyRobotShould, AcceptLeftRightActions)
{
    constexpr int X{2};
    constexpr int Y{3};
    const Position initialPose{X, Y, Direction::WEST};
    const Action placeAction({Action::Place{initialPose}});

    EXPECT_CALL(*mapMock, IsWithinRange(_)).WillRepeatedly(Return(true));
    sut->Act(placeAction);

    EXPECT_TRUE(sut->GetPosition() == initialPose);

    const Action leftAction{Action::Left{}};
    const Position newPose{X, Y, Direction::SOUTH};

    sut->Act(leftAction);
    EXPECT_TRUE(sut->GetPosition() == newPose);

    const Action rightAction{Action::Right{}};

    sut->Act(rightAction);
    EXPECT_TRUE(sut->GetPosition() == initialPose);
}

TEST_F(ToyRobotShould, RetainPositionWhenNewPositionNotWithinRange)
{
    constexpr int X{2};
    constexpr int Y{3};
    const Position initialPose{X, Y, Direction::WEST};
    const Action placeAction({Action::Place{initialPose}});

    EXPECT_CALL(*mapMock, IsWithinRange(_)).WillOnce(Return(true));
    sut->Act(placeAction);

    EXPECT_TRUE(sut->GetPosition() == initialPose);

    const Action moveAction{Action::Move{}};

    EXPECT_CALL(*mapMock, IsWithinRange(_)).WillOnce(Return(false));
    sut->Act(moveAction);
    EXPECT_TRUE(sut->GetPosition() == initialPose);

}
