cmake_minimum_required(VERSION 3.20)

include(../../config.cmake)

project(integration-tests LANGUAGES CXX)
message(STATUS "Packaging '${APP_NAME}':${PROJECT_NAME}")

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

file (GLOB_RECURSE MODULE_SRCS
    ${MODULE_PATH}/ToyRobotMovementTests.cpp
)

include_directories(
    ${APP_SOURCE_DIRECTORY}
    ${APP_ROOT_DIRECTORY}/tests
    ${APP_ROOT_DIRECTORY}/src
)

add_executable(${PROJECT_NAME}
    ${MODULE_SRCS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    app
    cmd
    map
    Catch2WithMain
)
