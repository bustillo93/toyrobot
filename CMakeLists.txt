cmake_minimum_required(VERSION 3.20)

include(config.cmake)

project(toy_robot LANGUAGES CXX)
message(STATUS "Packaging '${APP_NAME}':${PROJECT_NAME}")

set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(MODULE_SRCS
    ${MODULE_PATH}/main.cpp
)

add_executable(${PROJECT_NAME}
    ${MODULE_SRCS}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${MODULE_PATH}
    ${MODULE_PATH}/app
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    app
    cmd
    map
)

target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -Wpedantic -Werror
)

add_subdirectory(src/app/)
add_subdirectory(src/lib/)
add_subdirectory(src/map/)

add_subdirectory(tests/integration-tests/)
add_subdirectory(tests/unit-tests/)
