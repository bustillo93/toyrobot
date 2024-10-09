#include <catch2/catch.hpp>

#include "app/Application.hpp"
#include "lib/Position.hpp"

SCENARIO( "toy robot act on commands and report position", "[commands]" )
{
    using Position = lib::localisation::Position;
    using Direction = lib::localisation::Direction;

    GIVEN ("Toy robot in a table")
    {
        Application app{};

        WHEN ("PLACE heading EAST")
        {
            THEN ("MOVE")
            {
                std::list<std::string> cmds{
                    "PLACE 2, 1, EAST",
                    "MOVE",
                    "REPORT"
                };

                std::string actualPosition;
                Application::Output callback = [&actualPosition](const std::string& pos)
                {
                    actualPosition = pos;
                };
                app.Run(cmds, callback);

                REQUIRE(actualPosition == lib::localisation::Position(3, 1, Direction::EAST).ToString());
            }
            THEN ("RIGHT")
            {
                std::list<std::string> cmds{
                    "PLACE 2, 1, EAST",
                    "RIGHT",
                    "REPORT"
                };

                std::string actualPosition;
                Application::Output callback = [&actualPosition](const std::string& pos)
                {
                    actualPosition = pos;
                };
                app.Run(cmds, callback);

                REQUIRE(actualPosition == lib::localisation::Position(2, 1, Direction::SOUTH).ToString());
            }
        }
        WHEN ("PLACE heading NORTH")
        {
            THEN ("LEFT, MOVE, MOVE, MOVE, REPORT")
            {
                std::list<std::string> cmds{
                    "PLACE 2, 4, NORTH",
                    "LEFT",
                    "MOVE",
                    "MOVE",
                    "MOVE",
                    "REPORT"
                };

                std::string actualPosition;
                Application::Output callback = [&actualPosition](const std::string& pos)
                {
                    actualPosition = pos;
                };
                app.Run(cmds, callback);

                REQUIRE(actualPosition == lib::localisation::Position(0, 4, Direction::WEST).ToString());
            }
        }
    }
}
