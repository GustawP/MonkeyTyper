cmake_minimum_required(VERSION 3.24)
project(MonkeyType)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS OFF)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/_deps/sfml-src/cmake/Modules" ${CMAKE_MODULE_PATH})

add_executable(MonkeyType main.cpp)

target_link_libraries(MonkeyType sfml-graphics sfml-window sfml-system)