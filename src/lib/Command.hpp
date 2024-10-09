#pragma once

#include "lib/Position.hpp"

#include <string>
#include <variant>

namespace command
{
    struct Action
    {
        struct Report {};
        struct Right {};
        struct Left {};
        struct Move {};
        struct Place
        {
            lib::localisation::Position pos;
        };

        using ActionType = std::variant<Report, Right, Left, Move, Place>;
        ActionType cmdType;
    };

} // namespace command

