cmake_minimum_required(VERSION 3.20)

include(../../config.cmake)

project(map LANGUAGES CXX)
message(STATUS "Packaging '${APP_NAME}':${PROJECT_NAME}")

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(MODULE_SRCS
    ${MODULE_PATH}/ConcreteMap.cpp
)

add_library(${PROJECT_NAME} STATIC ${MODULE_SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${MODULE_PATH}
    ${APP_SOURCE_DIRECTORY}
)

target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -Wpedantic -Werror
)
