cmake_minimum_required(VERSION 3.20)

include(../../config.cmake)

project(unit_tests LANGUAGES CXX)
message(STATUS "Packaging '${APP_NAME}':${PROJECT_NAME}")

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../src)

file (GLOB_RECURSE MODULE_SRCS
    ${MODULE_PATH}/app/tests/*
    ${MODULE_PATH}/lib/tests/*
)

include_directories(
    ${MODULE_PATH}
)

add_executable(${PROJECT_NAME}
    ${MODULE_SRCS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    app
    cmd
    map
    gtest
    gtest_main
    gmock
)
