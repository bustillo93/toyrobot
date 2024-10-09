#include "app/Application.hpp"

#include <fstream>
#include <list>
#include <iostream>
#include <string>

int main(int argc,  char *argv[])
{
    std::cout << "This is a Toy Robot!\n";

    std::string fileName {"../tests/input-data/input.txt"};
    if (argc > 1)
    {
        fileName = argv[1];
    }

    std::ifstream fin;
    fin.open(fileName);
    std::string line;
    std::list<std::string> cmdList;

    while (std::getline(fin, line))
    {
        // insert to list
        cmdList.emplace_back(line);
    }

    Application app;
    app.Run(cmdList);

    fin.close();
    return 0;
}