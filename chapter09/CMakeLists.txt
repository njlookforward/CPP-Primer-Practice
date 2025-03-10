cmake_minimum_required(VERSION 3.5.0)
project(ChapterNineProject VERSION 0.1.0 LANGUAGES C CXX)

add_executable(ChapterNineProject ch09_main_exercise.cpp Sales_data.cpp exercise.cpp mydate.cpp)

include(CTest)
enable_testing()

