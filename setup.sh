#!/bin/sh

function runUnitTests()
{
    .\build\tests\unit-tests\unit_tests.exe
}

function runIntegrationTests()
{
    .\build\tests\integration-tests\integration-tests.exe
}

function runToyRobot()
{
    .\build\toy_robot.exe .\tests\input-data\input.txt
}
