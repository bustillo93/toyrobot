#include "Application.hpp"

#include "lib/Command.hpp"
#include "lib/parser/CommandParser.hpp"
#include "map/IMap.hpp"
#include "ToyRobot.hpp"

#include <iostream>

void Application::Run(std::list<std::string>& cmds, Output strOut)
{
    auto table{CreateConcreteMap(5, 5)};
    app::ToyRobot toyRobot{table};
    utils::CommandParser parser;

    auto callback = [&toyRobot, &strOut](const command::Action& cmd) -> bool
    {
        toyRobot.Act(cmd);
        if (strOut)
        {
            strOut(toyRobot.GetPosition().ToString());
        }
        return true;
    };

    for (const auto& cmd : cmds)
    {
        std::cout << cmd << "\n";
        if (cmd.empty())
        {
            toyRobot.Reset();
            continue;
        }
        parser.Parse(cmd, callback);
    }
}