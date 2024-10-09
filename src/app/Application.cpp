#include "Application.hpp"

#include "Command.hpp"
#include "CommandParser.hpp"
#include "IMap.hpp"
#include "ToyRobot.hpp"

#include <iostream>

void Application::Run(std::list<std::string>& cmds, Output strOut)
{
    auto table{CreateConcreteMap(5, 5)};
    app::ToyRobot toyRobot{table};
    cmd::CommandParser parser;

    auto callback = [&toyRobot, &strOut](const cmd::Action& cmd)
    {
        toyRobot.Act(cmd);
        if (strOut)
        {
            strOut(toyRobot.GetPosition().ToString());
        }
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