cmake_minimum_required(VERSION 3.16)
project(MiniTest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MiniTest INTERFACE)
add_library(MiniTest::MiniTest ALIAS MiniTest)

target_include_directories(MiniTest INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
