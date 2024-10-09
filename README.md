# Toy Robot Coding Challenge
The application is a simulation of a toy robot moving on a square table top.

## Overview
The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. There are no
other obstructions on the table surface. The robot is free to roam around the surface of the table, but must be prevented
from falling to destruction. Any movement that would result in the robot falling from the table must be prevented,
however further valid movement commands must still be allowed.

## How to setup?

### Requirements :
- gcc 7.1 (C++17)
- CMake 3.20 or newer added to environment path
- Visual Studio Code with CMake Tools extensions

## Compiling the src

#### Using Visual Studio Code
- Open the folder in Visual Studio Code
- CMake should start configuring the project but if not, select Terminal -> Configure Tasks.. and select C/C++: g++.exe active file which will add a proper entry in .vscode/tasks.json
- After succesful cmake configuration, press F7 to build
- Executables should be found in build folder

#### Using Docker
```
-- build docker image --
{project-dir}# docker build -t  toyrobot:001 .

-- run a docker container --
{project-dir}# docker run  --rm -it toyrobot:001

-- create and go to build folder --
# mkdir build
# cd build

-- configure and build CMake --
/build# cmake ..
/build# make
```

### Running the exe
```
-- run unit tests --
/build# ./tests/unit-tests/unit_tests

-- run integration tests --
/build# ./tests/integration-tests/integration-tests
```

### Running the binary with the input file
- Input file can be modified from `tests/input-data/input.txt`
```
/build# ./toy_robot ../tests/input-data/input.txt
```

