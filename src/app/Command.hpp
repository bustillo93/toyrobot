#pragma once

#include "Position.hpp"

#include <string>
#include <variant>

namespace cmd
{
    struct Action
    {
        struct Report {};
        struct Right {};
        struct Left {};
        struct Move {};
        struct Place
        {
            localisation::Position pos;
        };

        using ActionType = std::variant<Report, Right, Left, Move, Place>;
        ActionType cmdType;
    };

} // namespace cmd

