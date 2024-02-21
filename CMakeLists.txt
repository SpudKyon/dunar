cmake_minimum_required(VERSION 3.10)
project(dunar VERSION 0.1.0)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++20 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(include/)

find_library(YAMLCPP yaml-cpp)
find_package(GTest REQUIRED)

# Ragel文件生成对应的.cpp文件
ragelmaker(src/http11_parser.rl RLSRC ${PROJECT_SOURCE_DIR}/src)
ragelmaker(src/httpclient_parser.rl RLSRC ${PROJECT_SOURCE_DIR}/src)

set(SRC
        src/log.cpp
        src/util.cpp
        src/config.cpp
        src/thread.cpp
        src/fiber.cpp
        src/scheduler.cpp
        src/iomanager.cpp
        src/timer.cpp
        src/address.cpp
        src/fd_manager.cpp
        src/hook.cpp
        src/bytearray.cpp
        src/socket.cpp
        src/tcp_server.cpp
        src/http.cpp
        src/http_parser.cpp
        ${RLSRC}  # 包含生成的.cpp文件
)

set(TEST
        tests/log_test.cpp
        tests/config_test.cpp
        tests/thread_test.cpp
        tests/fiber_test.cpp
        tests/address_test.cpp
        tests/hook_test.cpp
        tests/bytearray_test.cpp
        tests/socket_test.cpp
        tests/http_test.cpp
        tests/http_parser_test.cpp
        tests/tcp_server_test.cpp
)

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
