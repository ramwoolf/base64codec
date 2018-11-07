cmake_minimum_required(VERSION 2.8)

project(base64_codec)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror")
add_executable(${PROJECT_NAME} "main.cpp")
