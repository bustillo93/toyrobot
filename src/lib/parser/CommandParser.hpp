#pragma once

#include "lib/Command.hpp"

#include <functional>
#include <optional>
#include <string>

namespace utils
{
class CommandParser
{
public:
    CommandParser(){}
    ~CommandParser(){}

    std::optional<command::Action> Parse(const std::string& str);
    bool Parse(const std::string& str, std::function<bool(const command::Action&)> func)
    {
        auto cmd = Parse(str);
        if (not cmd.has_value())
        {
            return false;
        }
        return func(*cmd);
    }
};

} // namespace utils
