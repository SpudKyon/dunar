cmake_minimum_required(VERSION 3.10)
project(dunar VERSION 0.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++20 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(include/)

find_library(YAMLCPP yaml-cpp)
find_package(GTest REQUIRED)

set(SRC
        src/log.cpp
        src/util.cpp
        src/config.cpp
        src/thread.cpp
        src/fiber.cpp
        src/scheduler.cpp
)

set(TEST
        tests/log_test.cpp
        tests/config_test.cpp
        tests/thread_test.cpp
        tests/fiber_test.cpp

)

#add_executable(dunar src/main.cpp)

add_executable(test
        tests/test.cpp
        ${SRC}
        ${TEST}
)

target_link_libraries(test
        ${YAMLCPP}
        GTest::GTest
        GTest::Main
)
