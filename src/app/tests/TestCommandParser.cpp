#include "app/CommandParser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

using ::testing::_;
using ::testing::Return;

using namespace cmd;

struct CommandParserShould : ::testing::Test
{
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    CommandParser sut{};

};

TEST_F(CommandParserShould, ParseCommandPlace)
{
    Action::Place expectedCmd{
        localisation::Position(1, 2, localisation::Direction::SOUTH)};

    std::optional<Action> actualAction = sut.Parse("PLACE 1,2,SOUTH");
    EXPECT_TRUE(actualAction.has_value());
    EXPECT_TRUE(std::holds_alternative<Action::Place>(actualAction.value().cmdType));
    EXPECT_TRUE(std::get<Action::Place>(actualAction.value().cmdType).pos == expectedCmd.pos);

    Action::Place expectedCmd2{
        localisation::Position(3, 4, localisation::Direction::NORTH)};

    actualAction = sut.Parse("PLACE 3,4,north");
    EXPECT_TRUE(actualAction.has_value());
    EXPECT_TRUE(std::holds_alternative<Action::Place>(actualAction.value().cmdType));
    EXPECT_TRUE(std::get<Action::Place>(actualAction.value().cmdType).pos == expectedCmd2.pos);
}

TEST_F(CommandParserShould, ParseCommandMove)
{
    Action::Move expectedCmd{};

    std::optional<Action> actualAction = sut.Parse("MOVE");
    EXPECT_TRUE(std::holds_alternative<Action::Move>(actualAction.value().cmdType));

    actualAction = sut.Parse("Move");
    EXPECT_TRUE(std::holds_alternative<Action::Move>(actualAction.value().cmdType));

    actualAction = sut.Parse("MOVEs");
    EXPECT_FALSE(actualAction.has_value());
}

TEST_F(CommandParserShould, ParseCommandRight)
{
    Action::Right expectedCmd{};

    std::optional<Action> actualAction = sut.Parse("RIGHT");
    EXPECT_TRUE(std::holds_alternative<Action::Right>(actualAction.value().cmdType));

    actualAction = sut.Parse("right");
    EXPECT_TRUE(std::holds_alternative<Action::Right>(actualAction.value().cmdType));

    actualAction = sut.Parse("R");
    EXPECT_FALSE(actualAction.has_value());
}

TEST_F(CommandParserShould, ParseCommandLeft)
{
    Action::Left expectedCmd{};

    std::optional<Action> actualAction = sut.Parse("LEFT");
    EXPECT_TRUE(std::holds_alternative<Action::Left>(actualAction.value().cmdType));

    actualAction = sut.Parse("left");
    EXPECT_TRUE(std::holds_alternative<Action::Left>(actualAction.value().cmdType));

    actualAction = sut.Parse("LEAF");
    EXPECT_FALSE(actualAction.has_value());
}

TEST_F(CommandParserShould, ParseCommandReport)
{
    Action::Report expectedCmd{};

    std::optional<Action> actualAction = sut.Parse("REPORT");
    EXPECT_TRUE(std::holds_alternative<Action::Report>(actualAction.value().cmdType));

    actualAction = sut.Parse("Report");
    EXPECT_TRUE(std::holds_alternative<Action::Report>(actualAction.value().cmdType));

    actualAction = sut.Parse("Rep0rt");
    EXPECT_FALSE(actualAction.has_value());
}

TEST_F(CommandParserShould, ParseInputCommands)
{
    std::vector<std::string> cmds = {
        "PLACE 2,1,EAST",
        "LEFT",
        "MOVE",
        "REPORT",
        "RIGHT"
    };

    int validCmdsCount = 0;
    auto dispatcher = [&validCmdsCount](const Action& action) -> bool
    {
        ++validCmdsCount;
        return true;
    };

    for (const auto& cmd : cmds)
    {
        sut.Parse(cmd, dispatcher);
    }

    EXPECT_EQ(cmds.size(), validCmdsCount);
}
