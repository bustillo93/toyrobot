cmake_minimum_required(VERSION 3.20)

include(../../config.cmake)

project(unit_tests LANGUAGES CXX)
message(STATUS "Packaging '${APP_NAME}':${PROJECT_NAME}")

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../src)

file (GLOB_RECURSE MODULE_SRCS
    ${MODULE_PATH}/app/tests/*
)

include_directories(
    ${MODULE_PATH}
)

include(FetchContent)
FetchContent_Declare(
  gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

add_executable(${PROJECT_NAME}
    ${MODULE_SRCS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    app
    gtest
    gtest_main
    gmock
)
