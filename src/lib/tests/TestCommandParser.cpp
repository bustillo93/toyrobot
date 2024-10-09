#include "lib/parser/CommandParser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

using ::testing::_;
using ::testing::Return;

struct CommandParserShould : ::testing::Test
{
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    utils::CommandParser sut{};

};

TEST_F(CommandParserShould, ParseCommandPlace)
{
    command::Action::Place expectedCmd{
        lib::localisation::Position(1, 2, lib::localisation::Direction::SOUTH)};

    std::optional<command::Action> actualAction = sut.Parse("PLACE 1,2,SOUTH");
    EXPECT_TRUE(actualAction.has_value());
    EXPECT_TRUE(std::holds_alternative<command::Action::Place>(actualAction.value().cmdType));
    EXPECT_TRUE(std::get<command::Action::Place>(actualAction.value().cmdType).pos == expectedCmd.pos);

    command::Action::Place expectedCmd2{
        lib::localisation::Position(3, 4, lib::localisation::Direction::NORTH)};

    actualAction = sut.Parse("PLACE 3,4,north");
    EXPECT_TRUE(actualAction.has_value());
    EXPECT_TRUE(std::holds_alternative<command::Action::Place>(actualAction.value().cmdType));
    EXPECT_TRUE(std::get<command::Action::Place>(actualAction.value().cmdType).pos == expectedCmd2.pos);
}

TEST_F(CommandParserShould, ParseCommandMove)
{
    command::Action::Move expectedCmd{};

    std::optional<command::Action> actualAction = sut.Parse("MOVE");
    EXPECT_TRUE(std::holds_alternative<command::Action::Move>(actualAction.value().cmdType));

    actualAction = sut.Parse("Move");
    EXPECT_TRUE(std::holds_alternative<command::Action::Move>(actualAction.value().cmdType));

    actualAction = sut.Parse("MOVEs");
    EXPECT_FALSE(actualAction.has_value());
}

TEST_F(CommandParserShould, ParseCommandRight)
{
    command::Action::Right expectedCmd{};

    std::optional<command::Action> actualAction = sut.Parse("RIGHT");
    EXPECT_TRUE(std::holds_alternative<command::Action::Right>(actualAction.value().cmdType));

    actualAction = sut.Parse("right");
    EXPECT_TRUE(std::holds_alternative<command::Action::Right>(actualAction.value().cmdType));

    actualAction = sut.Parse("R");
    EXPECT_FALSE(actualAction.has_value());
}

TEST_F(CommandParserShould, ParseCommandLeft)
{
    command::Action::Left expectedCmd{};

    std::optional<command::Action> actualAction = sut.Parse("LEFT");
    EXPECT_TRUE(std::holds_alternative<command::Action::Left>(actualAction.value().cmdType));

    actualAction = sut.Parse("left");
    EXPECT_TRUE(std::holds_alternative<command::Action::Left>(actualAction.value().cmdType));

    actualAction = sut.Parse("LEAF");
    EXPECT_FALSE(actualAction.has_value());
}

TEST_F(CommandParserShould, ParseCommandReport)
{
    command::Action::Report expectedCmd{};

    std::optional<command::Action> actualAction = sut.Parse("REPORT");
    EXPECT_TRUE(std::holds_alternative<command::Action::Report>(actualAction.value().cmdType));

    actualAction = sut.Parse("Report");
    EXPECT_TRUE(std::holds_alternative<command::Action::Report>(actualAction.value().cmdType));

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
    auto dispatcher = [&validCmdsCount](const command::Action& action) -> bool
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
