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
- CMake 3.20 or newer
- GTest/GMock for unit testing

### Using Docker image :
- locally installed Docker engine
- build the docker image using the provided bash script
```
{project-dir}# ./scripts/build_docker.sh
```
- and run a container
```
{project-dir}# ./scripts/run_docker.sh
```

## Compiling the src
- From project-dir as current directory,
```
-- go to build folder --
{project-dir}# cd build

-- configure and build CMake --
{project-dir}/build# cmake ..
{project-dir}/build# make

-- run unit tests --
{project-dir}/build# ./tests/unit-tests/unit_tests

-- run integration tests --
{project-dir}/build# ./tests/integration-tests/integration-tests
```
- Alternatively, you can use the scripts provided
```
-- configure and build CMake --
{project-dir}# ./scripts/build_src.sh

-- run unit tests --
{project-dir}# ./scripts/run_unit_tests.sh

-- run integration tests --
{project-dir}# ./scripts/run_integration_tests.sh
```

### Running the binary with the input file
- Input file can be modified from `tests/input-data/input.txt`
```
{project-dir}/build# ./toy_robot
```
- or using the script
```
{project-dir}# ./scripts/run_toy_robot.sh
```

