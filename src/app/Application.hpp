#pragma once

#include <functional>
#include <list>
#include <string>

class Application
{
public:
    using Output = std::function<void(const std::string&)>;

    Application(){}
    ~Application(){}

    void Run(std::list<std::string>& cmds, Output strOut = nullptr);
};
