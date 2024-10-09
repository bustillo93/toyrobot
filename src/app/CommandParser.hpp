#pragma once

#include "Command.hpp"

#include <functional>
#include <optional>
#include <string>

namespace cmd
{
class CommandParser
{
public:
    CommandParser(){}
    ~CommandParser(){}

    std::optional<cmd::Action> Parse(const std::string& str);
    bool Parse(const std::string& str, std::function<void(const cmd::Action&)> func)
    {
        auto cmd = Parse(str);
        if (! cmd.has_value())
        {
            return false;
        }

        func(*cmd);
        return true;
    }
};

} // namespace cmd
