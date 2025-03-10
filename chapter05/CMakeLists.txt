cmake_minimum_required(VERSION 3.5.0)
project(ChapterFiveProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterFiveProject ch05_main.cpp Sales_item.cpp)

include(CTest)
enable_testing()

